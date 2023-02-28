#include "UnitInformationListWidget.h"
#include "UnitInformationWidget.h"

void UUnitInformationListWidget::AddUnit(FUnit* Unit)
{
	CheckWidgetsMapState(Unit);
	Widgets[Unit->GetCountryController()]->AddUnit(Unit);
}

void UUnitInformationListWidget::RemoveUnit(FUnit* Unit)
{
	Widgets[Unit->GetCountryController()]->RemoveUnit(Unit);
	CheckWidgetsMapState(Unit);
}

void UUnitInformationListWidget::CheckWidgetsMapState(FUnit* Unit)
{
	if (!Widgets.Contains(Unit->GetCountryController()))
	{
		UUnitInformationWidget* Widget = CreateWidget<UUnitInformationWidget>(GetWorld(), UnitInformationWidgetClass);
		Widget->Init();
		Widgets.Add(Unit->GetCountryController(), Widget);
		UnitsGridPanel->AddChildToGrid(Widget, Widgets.Num());
	} else if (Widgets[Unit->GetCountryController()]->IsEmpty())
	{
		UnitsGridPanel->RemoveChild(Widgets[Unit->GetCountryController()]);
		Widgets.Remove(Unit->GetCountryController());
	}
}
