#include "Widgets/Military/Collections/UnitsCollectionGroupsWidget.h"

bool UUnitsCollectionGroupsWidget::AddUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	UnitsCollectionGroupsListView->AddItem(UnitsCollectionGroup);
	return false;
}

bool UUnitsCollectionGroupsWidget::RemoveUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	UnitsCollectionGroupsListView->RemoveItem(UnitsCollectionGroup);
	return !UnitsCollectionGroupsListView->GetNumItems();
}
