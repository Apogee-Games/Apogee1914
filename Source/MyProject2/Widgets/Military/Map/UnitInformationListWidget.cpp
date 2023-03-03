#include "UnitInformationListWidget.h"
#include "UnitInformationWidget.h"

void UUnitInformationListWidget::AddUnit(UUnit* Unit)
{
	CheckWidgetsMapState(Unit);
	Widgets[Unit->GetCountryController()]->AddUnit(Unit);
}

void UUnitInformationListWidget::RemoveUnit(UUnit* Unit)
{
	Widgets[Unit->GetCountryController()]->RemoveUnit(Unit);
	CheckWidgetsMapState(Unit);
}

void UUnitInformationListWidget::CheckWidgetsMapState(UUnit* Unit)
{
	UCountry* Country = Unit->GetCountryController();
	if (!Widgets.Contains(Country))
	{
		UUnitsListCarrier* UnitsListCarrier = NewObject<UUnitsListCarrier>();
		UnitsListView->AddItem(UnitsListCarrier);
		Widgets.Add(Country, UnitsListCarrier);
	} else if (Widgets[Country]->IsEmpty())
	{
		UnitsListView->RemoveItem(Widgets[Country]);
		Widgets.Remove(Country);
	}
}
