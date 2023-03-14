#include "Widgets/Military/Selection/SelectedUnitsListWidget.h"

#include "Military/Instances/Units/Unit.h"

void USelectedUnitsListWidget::SetSelectedUnits(const TSet<UUnit*>& Units)
{
	SelectedUnitsWidget->SetSelectedUnits(Units);
}

void USelectedUnitsListWidget::SetSelectedUnits(const TSet<UUnitsCollection*>& UnitsCollections)
{
	UnitsCollectionsListView->ClearListItems();
	for (const auto UnitsCollection: UnitsCollections)
	{
		UnitsCollectionsListView->AddItem(UnitsCollection);
	}
}

void USelectedUnitsListWidget::SetSelectedUnits(const TSet<UUnitsCollectionGroup*>& UnitsCollectionGroups)
{
	UnitsCollectionGroupsListView->ClearListItems();
	for (const auto UnitsCollection: UnitsCollectionGroups)
	{
		UnitsCollectionGroupsListView->AddItem(UnitsCollection);
	}
}
