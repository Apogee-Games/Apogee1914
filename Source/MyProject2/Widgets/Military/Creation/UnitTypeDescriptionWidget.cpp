#include "UnitTypeDescriptionWidget.h"

void UUnitTypeDescriptionWidget::Init(const FUnitDescription* UnitDescription)
{
	SetUnitName(UnitDescription->UnitName);
}

void UUnitTypeDescriptionWidget::SetUnitName(const FName& UnitName)
{
	UnitNameTextBlock->SetText(FText::FromName(UnitName));
}
