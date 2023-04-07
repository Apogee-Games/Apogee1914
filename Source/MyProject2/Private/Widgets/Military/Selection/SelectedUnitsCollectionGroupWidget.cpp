#include "Widgets/Military/Selection/SelectedUnitsCollectionGroupWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/CommanderSelectionPawnState.h"
#include "Military/Descriptions/MilitaryBranchDescription.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedUnitsCollectionGroupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &USelectedUnitsCollectionGroupWidget::OnButtonClick);
	RemoveUnitsCollectionGroupButton->OnClicked.AddDynamic(this, &USelectedUnitsCollectionGroupWidget::OnRemoveUnitsCollectionGroupButton);
	CommanderButton->OnClicked.AddDynamic(this, &USelectedUnitsCollectionGroupWidget::OnCommanderButtonClick);
}

void USelectedUnitsCollectionGroupWidget::SetSelectedUnits(UObject* ProvidedUnitsCollectionGroup)
{
	UnitsCollectionGroup = Cast<UUnitsCollectionGroup>(ProvidedUnitsCollectionGroup);
}

void USelectedUnitsCollectionGroupWidget::RefreshData()
{
	UnitsCollectionListView->ClearListItems();
	for (const auto& UnitsCollection: UnitsCollectionGroup->GetAll())
	{
		UnitsCollectionListView->AddItem(UnitsCollection);
	}

	UnitsCollectionNumberTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollectionGroup->GetSize())));
	
	MilitaryBranchTextBlock->SetText(UnitsCollectionGroup->GetMilitaryBranch()->Name);

	UPerson* Commander = UnitsCollectionGroup->GetCommander();
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

void USelectedUnitsCollectionGroupWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(UnitsCollectionGroup);
}

void USelectedUnitsCollectionGroupWidget::OnRemoveUnitsCollectionGroupButton()
{
	UUnitsSelectionComponent* SelectionComponent = GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent;

	SelectionComponent->UnSelectUnits(UnitsCollectionGroup);
	SelectionComponent->SelectUnits(UnitsCollectionGroup->GetAll(), true, true);

	GetGameInstance()->GetSubsystem<UUnitsFactory>()->RemoveUnitCollectionGroup(UnitsCollectionGroup);
}

void USelectedUnitsCollectionGroupWidget::OnCommanderButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetCommandable(UnitsCollectionGroup);
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FCommanderSelectionPawnState::GetInstance());
}
