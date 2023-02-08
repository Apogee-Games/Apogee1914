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
	if (!Widgets.Contains(Unit->GetCountryController()))
	{
		UUnitInformationWidget* Widget = CreateWidget<UUnitInformationWidget>(GetWorld(), UnitInformationWidgetClass);
		Widgets.Add(Unit->GetCountryController(),  Widget);
		UnitsGridPanel->AddChildToGrid(Widget, Widgets.Num());
	} else if (Widgets[Unit->GetCountryController()]->IsEmpty())
	{
		UnitsGridPanel->RemoveChild(Widgets[Unit->GetCountryController()]);
		Widgets.Remove(Unit->GetCountryController());
	}
}
