
#include "Widgets/Military/Selection/SelectedUnitsWidget.h"

void USelectedUnitsWidget::SetSelectedUnits(const TSet<UUnit*>& Units) const
{
	UnitsListView->ClearListItems();
	for (const auto& Unit: Units)
	{
		UnitsListView->AddItem(Unit);
	}

	UnitsNumberTextBlock->SetText(FText::FromString(FString::FromInt(Units.Num())));
}
