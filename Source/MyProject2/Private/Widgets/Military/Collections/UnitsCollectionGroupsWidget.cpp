#include "Widgets/Military/Collections/UnitsCollectionGroupsWidget.h"

void UUnitsCollectionGroupsWidget::AddUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	UnitsCollectionGroupsListView->AddItem(UnitsCollectionGroup);
}

void UUnitsCollectionGroupsWidget::RemoveUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	UnitsCollectionGroupsListView->RemoveItem(UnitsCollectionGroup);
}
