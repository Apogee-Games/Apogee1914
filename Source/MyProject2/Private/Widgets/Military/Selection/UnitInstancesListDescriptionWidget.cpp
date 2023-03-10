#include "Widgets/Military/Selection/UnitInstancesListDescriptionWidget.h"

#include "Military/Instances/Units/Unit.h"

void UUnitInstancesListDescriptionWidget::SetSelectedUnits(const TArray<UUnit*>& Units) const
{
	UnitsListView->ClearListItems();
	for (const auto& Unit: Units)
	{
		UnitsListView->AddItem(Unit);
	}
}