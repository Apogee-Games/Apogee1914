#include "Widgets/Military/Collections/UnitCollectionGroupWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/CommanderSelectionPawnState.h"

void UUnitCollectionGroupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UUnitCollectionGroupWidget::OnButtonClick);
	CommanderButton->OnClicked.AddDynamic(this, &UUnitCollectionGroupWidget::OnCommanderButtonClick);
}

void UUnitCollectionGroupWidget::SetUnitsCollectionGroup(UObject* ProvidedUnitsCollectionGroup)
{
	UnitsCollectionGroup = Cast<UUnitsCollectionGroup>(ProvidedUnitsCollectionGroup);
}

void UUnitCollectionGroupWidget::RefreshData()
{
	UnitsCollectionsListView->ClearListItems();

	for (const auto& UnitsCollection: UnitsCollectionGroup->GetAll())
	{
		UnitsCollectionsListView->AddItem(UnitsCollection);
	}
	
	const FName MilitaryBranchName = MilitaryBranchesNames[static_cast<int>(UnitsCollectionGroup->GetMilitaryBranch())];
	MilitaryBranchTextBlock->SetText(FText::FromName(MilitaryBranchName));
	
	CollectionGroupSizeTextBlock->SetText(FText::FromString(FString::FromInt(UnitsCollectionGroup->GetSize())));

	const UPerson* Commander = UnitsCollectionGroup->GetCommander();
	
	if (Commander)
	{
		CommanderImage->SetBrushResourceObject(Commander->GetImage());
		//CommanderNameTextBlock->SetText(FText::FromName(Commander->GetPersonName()));
	} else
	{
		CommanderImage->SetBrushResourceObject(nullptr);
		//CommanderNameTextBlock->SetText(FText::FromString(TEXT("None")));
	}
}

void UUnitCollectionGroupWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnitSelectionComponent->SelectUnits(UnitsCollectionGroup);
}

void UUnitCollectionGroupWidget::OnCommanderButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetCommandable(UnitsCollectionGroup);
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FCommanderSelectionPawnState::GetInstance());
}
