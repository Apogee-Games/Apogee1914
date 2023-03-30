#include "Widgets/Military/Collections/MilitaryBranchUnitsCollectionsListWidget.h"

void UMilitaryBranchUnitsCollectionsListWidget::AddUnitsCollection(UUnitsCollection* UnitsCollection) {
	UnitsCollectionsWidget->AddUnitsCollection(UnitsCollection);
}

void UMilitaryBranchUnitsCollectionsListWidget::RemoveUnistCollection(UUnitsCollection* UnitsCollection)
{
	UnitsCollectionsWidget->RemoveUnitsCollection(UnitsCollection);
}

void UMilitaryBranchUnitsCollectionsListWidget::AddUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	UnitsCollectionGroupsWidget->AddUnitsCollectionGroup(UnitsCollectionGroup);
}

void UMilitaryBranchUnitsCollectionsListWidget::RemoveUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	UnitsCollectionGroupsWidget->RemoveUnitsCollectionGroup(UnitsCollectionGroup);
}
