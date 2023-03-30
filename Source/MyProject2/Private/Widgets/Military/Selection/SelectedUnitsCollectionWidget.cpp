
#include "Widgets/Military/Selection/SelectedUnitsCollectionWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/CommanderSelectionPawnState.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedUnitsCollectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &USelectedUnitsCollectionWidget::OnButtonClick);
	RemoveUnitsCollectionButton->OnClicked.AddDynamic(this, &USelectedUnitsCollectionWidget::OnRemoveUnitsCollectionButtonClick);
	CommanderButton->OnClicked.AddDynamic(this, &USelectedUnitsCollectionWidget::OnCommanderButtonClick);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitRemovalObserver(this);
}

void USelectedUnitsCollectionWidget::SetSelectedUnits(UObject* ProvidedUnitsCollection)
{
	UnitsCollection = Cast<UUnitsCollection>(ProvidedUnitsCollection);
}

void USelectedUnitsCollectionWidget::RefreshData()
{
	UnitsListView->ClearListItems();
	for (const auto& Unit: UnitsCollection->GetAll())
	{
		UnitsListView->AddItem(Unit);
	}

	UnitsNumberTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollection->GetSize())));

	const FName MilitaryBranchName = MilitaryBranchesNames[static_cast<int>(UnitsCollection->GetMilitaryBranch())];
	MilitaryBranchTextBlock->SetText(FText::FromName(MilitaryBranchName));

	UPerson* Commander = UnitsCollection->GetCommander();
	if (Commander)
	{
		CommanderImage->SetBrushResourceObject(Commander->GetImage());
		CommanderNameTextBlock->SetText(FText::FromName(Commander->GetPersonName()));
	} else
	{
		CommanderImage->SetBrushResourceObject(nullptr);
		CommanderNameTextBlock->SetText(FText::FromString(TEXT("None")));
	}
}

void USelectedUnitsCollectionWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetSubsystem<UUnitsFactory>()->RemoveUnitRemovalObserver(this);
}

void USelectedUnitsCollectionWidget::UnitIsRemoved(UUnit* Unit)
{
	UnitsListView->RemoveItem(Unit);
}

void USelectedUnitsCollectionWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(UnitsCollection);
}

void USelectedUnitsCollectionWidget::OnRemoveUnitsCollectionButtonClick()
{
	UUnitsSelectionComponent* SelectionComponent = GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent;

	SelectionComponent->SelectUnits(UnitsCollection->GetAll(), false, true);
	
	GetWorld()->GetSubsystem<UUnitsFactory>()->RemoveUnitCollection(UnitsCollection);
	
	SelectionComponent->UnSelectUnits(UnitsCollection, true);
}

void USelectedUnitsCollectionWidget::OnCommanderButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetCommandable(UnitsCollection);
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FCommanderSelectionPawnState::GetInstance());
}
