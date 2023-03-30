#include "Widgets/Military/Collections/UnitsCollectionsWidget.h"

void UUnitsCollectionsWidget::AddUnitsCollection(UUnitsCollection* UnitsCollection)
{
	UnitsCollections.Add(UnitsCollection);
}

void UUnitsCollectionsWidget::RemoveUnitsCollection(UUnitsCollection* UnitsCollection)
{
	UnitsCollections.Remove(UnitsCollection);
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
