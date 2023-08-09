
#include "Widgets/Military/Selection/SelectedUnitsCollectionWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/CommanderSelectionPawnState.h"
#include "Military/Descriptions/MilitaryBranchDescription.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedUnitsCollectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button->OnClicked.AddDynamic(this, &USelectedUnitsCollectionWidget::OnButtonClick);
	RemoveUnitsCollectionButton->OnClicked.AddDynamic(this, &USelectedUnitsCollectionWidget::OnRemoveUnitsCollectionButtonClick);
	CommanderButton->OnClicked.AddDynamic(this, &USelectedUnitsCollectionWidget::OnCommanderButtonClick);

	UnitsFactory = GetGameInstance()->GetSubsystem<UUnitsFactory>();
	UnitsFactory->OnUnitStatusChanged.AddUObject(this, &ThisClass::OnUnitStatusChanged);
}

void USelectedUnitsCollectionWidget::NativeDestruct()
{
	Super::NativeDestruct();

	Button->OnClicked.RemoveAll(this);
	RemoveUnitsCollectionButton->OnClicked.RemoveAll(this);
	CommanderButton->OnClicked.RemoveAll(this);
	
	UnitsFactory->OnUnitStatusChanged.RemoveAll(this);
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

	UnitsNumberTextBlock->SetText(FText::AsNumber(UnitsCollection->GetSize()));

	MilitaryBranchTextBlock->SetText(UnitsCollection->GetMilitaryBranch()->Name);

	UPerson* Commander = UnitsCollection->GetCommander();
	if (Commander)
	{
		CommanderImage->SetBrushResourceObject(Commander->GetImage());
		CommanderNameTextBlock->SetText(Commander->GetPersonName());
	} else
	{
		CommanderImage->SetBrushResourceObject(nullptr);
		CommanderNameTextBlock->SetText(FText::FromString(TEXT("None")));
	}
}

void USelectedUnitsCollectionWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(UnitsCollection);
}

void USelectedUnitsCollectionWidget::OnRemoveUnitsCollectionButtonClick()
{
	UUnitsSelectionComponent* SelectionComponent = GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent;

	SelectionComponent->SelectUnits(UnitsCollection->GetAll(), false, true);
	
	UnitsFactory->RemoveUnitCollection(UnitsCollection);
	
	SelectionComponent->UnSelectUnits(UnitsCollection, true); // TODO: Add subscription to removal instead
}

void USelectedUnitsCollectionWidget::OnCommanderButtonClick()
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	Pawn->SetCommandable(UnitsCollection);
	Pawn->SetPawnState(FCommanderSelectionPawnState::GetInstance());
}

void USelectedUnitsCollectionWidget::OnUnitStatusChanged(UUnit* Unit, EUnitStatus UnitStatus)
{
	if (UnitStatus == EUnitStatus::Dissolved)
	{
		UnitsListView->RemoveItem(Unit);
	}
}
