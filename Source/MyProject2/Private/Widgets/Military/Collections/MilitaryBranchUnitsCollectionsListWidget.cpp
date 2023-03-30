#include "Widgets/Military/Collections/MilitaryBranchUnitsCollectionsListWidget.h"

void UMilitaryBranchUnitsCollectionsListWidget::Init(EMilitaryBranch MilitaryBranch)
{
	Border->BrushColor = MilitaryBranchesColors[MilitaryBranch];
	UpdateVisibility();
}

void UMilitaryBranchUnitsCollectionsListWidget::AddUnitsCollection(UUnitsCollection* UnitsCollection) {
	IsUnitsCollectionsEmpty = UnitsCollectionsWidget->AddUnitsCollection(UnitsCollection);
	UpdateVisibility();
}

void UMilitaryBranchUnitsCollectionsListWidget::RemoveUnistCollection(UUnitsCollection* UnitsCollection)
{
	IsUnitsCollectionsEmpty = UnitsCollectionsWidget->RemoveUnitsCollection(UnitsCollection);
	UpdateVisibility();
}

void UMilitaryBranchUnitsCollectionsListWidget::AddUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	IsUnitsCollectionsGroupsEmpty = UnitsCollectionGroupsWidget->AddUnitsCollectionGroup(UnitsCollectionGroup);
	UpdateVisibility();
}

void UMilitaryBranchUnitsCollectionsListWidget::RemoveUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	IsUnitsCollectionsGroupsEmpty = UnitsCollectionGroupsWidget->RemoveUnitsCollectionGroup(UnitsCollectionGroup);
	UpdateVisibility();
}

void UMilitaryBranchUnitsCollectionsListWidget::UpdateVisibility()
{
	if (IsUnitsCollectionsEmpty && IsUnitsCollectionsGroupsEmpty)
	{
		SetVisibility(ESlateVisibility::Collapsed);
	} else
	{
		SetVisibility(ESlateVisibility::Visible);
	}
}
