
#include "Widgets/Military/Creation/UnitTypesListWidget.h"
#include "Widgets/Military/Carriers/UnitDescriptionCarrier.h"

void UUnitTypesListWidget::AddUnitType(FUnitDescription* UnitDescription)
{
	UUnitDescriptionCarrier* UnitDescriptionCarrier = NewObject<UUnitDescriptionCarrier>();
	UnitDescriptionCarrier->Init(UnitDescription);
	UnitDescriptionListView->AddItem(UnitDescriptionCarrier);
}
