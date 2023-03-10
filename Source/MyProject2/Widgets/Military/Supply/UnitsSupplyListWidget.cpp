#include "UnitsSupplyListWidget.h"

#include "MyProject2/Military/Managers/UnitsFactory.h"
#include "MyProject2/Military/Managers/UnitsSupplyController.h"

void UUnitsSupplyListWidget::Init()
{
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
}

void UUnitsSupplyListWidget::UnitIsCreated(UUnit* Unit)
{
	UnitsListView->AddItem(Unit);
}
// TODO: Add OnUnitRemove :)