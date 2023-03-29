#include "Widgets/Military/Selection/SelectedMilitaryBranchUnitsListWidget.h"

void USelectedMilitaryBranchUnitsListWidget::Init(EMilitaryBranch MilitaryBranch)
{
	SelectedUnitsWidget->Init(MilitaryBranch);
	MilitaryBranchTextBlock->SetText(FText::FromName(MilitaryBranchNames[MilitaryBranch]));
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
	if (Selection.SelectedUnits.Num())
	{
		SelectedUnitsWidget->SetVisibility(ESlateVisibility::Visible);
	} else
	{
		SelectedUnitsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void USelectedMilitaryBranchUnitsListWidget::AddUnitsCollection(const FUnitsSelection& Selection)
{
	UnitsCollectionsListView->ClearListItems();
	for (const auto UnitsCollection: Selection.SelectedUnitsCollections)
	{
		UnitsCollectionsListView->AddItem(UnitsCollection);
	}
}

void USelectedMilitaryBranchUnitsListWidget::AddUnitsCollectionsGroups(const FUnitsSelection& Selection)
{
	UnitsCollectionGroupsListView->ClearListItems();
	for (const auto UnitsCollectionGroup: Selection.SelectedUnitsCollectionGroups)
	{
		UnitsCollectionGroupsListView->AddItem(UnitsCollectionGroup);
	}
}
