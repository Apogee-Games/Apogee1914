#include "UnitsSupplyListWidget.h"

#include "MyProject2/Military/Managers/UnitsFactory.h"
#include "MyProject2/Military/Managers/UnitsSupplyController.h"

void UUnitsSupplyListWidget::Init()
{
	GetWorld()->GetSubsystem<UUnitsSupplyController>()->AddUnitSupplyObserver(this);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
}

void UUnitsSupplyListWidget::UnitIsCreated(FUnit* Unit)
{
	UUnitSupplyWidget* Widget = CreateWidget<UUnitSupplyWidget>(GetWorld(), UnitSupplyWidgetClass);
	Widget->Init(Unit);
	Widgets.Add(Unit, Widget);
	ListGridPanel->AddChildToGrid(Widget, Count);
	Count++;
}

void UUnitsSupplyListWidget::UnitIsSupplied(FUnit* Unit)
{
	Widgets[Unit]->UnitWasSupplied(Unit);
}
