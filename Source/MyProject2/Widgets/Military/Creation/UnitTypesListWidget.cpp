#include "UnitTypesListWidget.h"

#include "Components/Button.h"
#include "MyProject2/Military/Instances/UnitDescriptionCarrier.h"

void UUnitTypesListWidget::AddUnitType(FUnitDescription* UnitDescription)
{
	UUnitDescriptionCarrier* UnitDescriptionCarrier = NewObject<UUnitDescriptionCarrier>();
	UnitDescriptionCarrier->Init(UnitDescription);
	UnitDescriptionListView->AddItem(UnitDescriptionCarrier);
}
