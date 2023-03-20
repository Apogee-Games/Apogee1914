
#include "Widgets/Military/Supply/UnitsSupplyListWidget.h"

#include "Military/Managers/UnitsFactory.h"
#include "Military/Managers/UnitsSupplyController.h"

void UUnitsSupplyListWidget::Init()
{
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
}

void UUnitsSupplyListWidget::UnitIsCreated(UUnit* Unit)
{
	UnitsListView->AddItem(Unit);
}

void UUnitsSupplyListWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetSubsystem<UUnitsFactory>()->RemoveUnitCreationObserver(this);
}
// TODO: Add OnUnitRemove :)
