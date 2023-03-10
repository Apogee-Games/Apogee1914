#include "UnitTypesListWidget.h"

#include "MyProject2/Widgets/Military/Carriers/UnitDescriptionCarrier.h"

void UUnitTypesListWidget::AddUnitType(FUnitDescription* UnitDescription)
{
	UUnitDescriptionCarrier* UnitDescriptionCarrier = NewObject<UUnitDescriptionCarrier>();
	UnitDescriptionCarrier->Init(UnitDescription);
	UnitDescriptionListView->AddItem(UnitDescriptionCarrier);
}
