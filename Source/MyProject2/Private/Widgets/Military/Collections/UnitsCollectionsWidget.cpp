#include "Widgets/Military/Collections/UnitsCollectionsWidget.h"

bool UUnitsCollectionsWidget::AddUnitsCollection(UUnitsCollection* UnitsCollection)
{
	UnitsCollections.Add(UnitsCollection);
	return false;
}

bool UUnitsCollectionsWidget::RemoveUnitsCollection(UUnitsCollection* UnitsCollection)
{
	UnitsCollections.Remove(UnitsCollection);
	return UnitsCollections.IsEmpty();
}

void UUnitsCollectionsWidget::RefreshData()
{
	UnitsCollectionsListView->ClearListItems();
	for (const auto& UnitsCollection: UnitsCollections)
	{
		if (UnitsCollection->GetUnitsCollectionGroup()) continue;
		UnitsCollectionsListView->AddItem(UnitsCollection);
	}
}
