#include "Widgets/Military/Collections/MilitaryBranchUnitsCollectionsListWidget.h"

#include "Military/Descriptions/MilitaryBranchDescription.h"

void UMilitaryBranchUnitsCollectionsListWidget::Init(UMilitaryBranchDescription* MilitaryBranch)
{
	Border->BrushColor = MilitaryBranch->Color;
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
