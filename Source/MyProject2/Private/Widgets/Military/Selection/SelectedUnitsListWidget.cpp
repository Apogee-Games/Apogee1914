#include "Widgets/Military/Selection/SelectedUnitsListWidget.h"

#include "Military/Instances/Units/Unit.h"

void USelectedUnitsListWidget::Init()
{
	SelectedUnitsWidget->Init();
}

void USelectedUnitsListWidget::SetSelectedUnits(const TSet<UUnit*>& Units)
{
	SelectedUnitsWidget->SetSelectedUnits(Units);
	if (Units.Num())
	{
		SelectedUnitsWidget->SetVisibility(ESlateVisibility::Visible);
	} else
	{
		SelectedUnitsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
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
	for (const auto UnitsCollectionGroup: UnitsCollectionGroups)
	{
		UnitsCollectionGroupsListView->AddItem(UnitsCollectionGroup);
	}
}
