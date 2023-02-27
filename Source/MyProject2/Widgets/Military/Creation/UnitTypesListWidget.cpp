#include "UnitTypesListWidget.h"

#include "Components/Button.h"

void UUnitTypesListWidget::AddUnitType(const FUnitDescription* UnitDescription)
{
	UUnitTypeDescriptionWidget* UnitTypeDescriptionWidget = CreateWidget<UUnitTypeDescriptionWidget>(GetWorld(), UnitDescriptionWidgetClass);
	UnitTypeDescriptionWidget->Init(UnitDescription);
	ListGridPanel->AddChildToGrid(UnitTypeDescriptionWidget, Count);
	++Count;
}
