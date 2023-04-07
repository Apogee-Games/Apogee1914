#include "Widgets/Military/Selection/SelectedMilitaryBranchUnitsListWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Descriptions/MilitaryBranchDescription.h"
#include "Military/Managers/UnitsFactory.h"

void USelectedMilitaryBranchUnitsListWidget::Init(UMilitaryBranchDescription* ProvidedMilitaryBranch)
{
	MilitaryBranch = ProvidedMilitaryBranch;
	SelectedUnitsWidget->Init(MilitaryBranch);
	MilitaryBranchTextBlock->SetText(MilitaryBranch->Name);
	MilitaryBranchExpandableArea->BorderBrush.TintColor = MilitaryBranch->Color;
	
	CreateUnitsCollectionGroupButton->OnClicked.AddDynamic(this, &USelectedMilitaryBranchUnitsListWidget::OnCreateUnitsCollectionGroupButtonClick);
}

void USelectedMilitaryBranchUnitsListWidget::SetSelection(const FUnitsSelection& Selection)
{
	AddUnits(Selection);
	AddUnitsCollection(Selection);
	AddUnitsCollectionsGroups(Selection);
	
	if (Selection.IsEmpty())
	{
		SetVisibility(ESlateVisibility::Collapsed);
	} else
	{
		SetVisibility(ESlateVisibility::Visible);
	}
}

void USelectedMilitaryBranchUnitsListWidget::AddUnits(const FUnitsSelection& Selection)
{
	SelectedUnitsWidget->SetSelectedUnits(Selection.SelectedUnits);
	
	if (Selection.SelectedUnits.IsEmpty())
	{
		SelectedUnitsWidget->SetVisibility(ESlateVisibility::Collapsed);
	} else
	{
		SelectedUnitsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void USelectedMilitaryBranchUnitsListWidget::AddUnitsCollection(const FUnitsSelection& Selection)
{
	UnitsCollectionsListView->ClearListItems();
	for (const auto UnitsCollection: Selection.SelectedUnitsCollections)
	{
		UnitsCollectionsListView->AddItem(UnitsCollection);
	}
	
	if (Selection.SelectedUnitsCollections.IsEmpty())
	{
		UnitsCollectionsExpandableArea->SetVisibility(ESlateVisibility::Collapsed);
	} else
	{
		UnitsCollectionsExpandableArea->SetVisibility(ESlateVisibility::Visible);
	}
}

void USelectedMilitaryBranchUnitsListWidget::AddUnitsCollectionsGroups(const FUnitsSelection& Selection)
{
	UnitsCollectionGroupsListView->ClearListItems();
	for (const auto UnitsCollectionGroup: Selection.SelectedUnitsCollectionGroups)
	{
		UnitsCollectionGroupsListView->AddItem(UnitsCollectionGroup);
	}
	
	if (Selection.SelectedUnitsCollectionGroups.IsEmpty())
	{
		UnitsCollectionGroupsExpandableArea->SetVisibility(ESlateVisibility::Collapsed);
	} else
	{
		UnitsCollectionGroupsExpandableArea->SetVisibility(ESlateVisibility::Visible);
	}
}

void USelectedMilitaryBranchUnitsListWidget::OnCreateUnitsCollectionGroupButtonClick()
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();

	const TArray<UUnitsCollection*>& UnitsCollections = reinterpret_cast<const TArray<UUnitsCollection*>&>(UnitsCollectionsListView->GetListItems());
	Pawn->UnitSelectionComponent->UnSelectUnits(UnitsCollections);

	UUnitsCollectionGroup* UnitsCollectionGroup = GetGameInstance()->GetSubsystem<UUnitsFactory>()->CreateUnitCollectionGroup(MilitaryBranch, Pawn->GetRuledCountry(), UnitsCollections);

	Pawn->UnitSelectionComponent->SelectUnits(UnitsCollectionGroup);
}
