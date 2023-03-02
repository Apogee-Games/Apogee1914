#include "UnitTypeEquipmentRequirementWidget.h"

void UUnitTypeEquipmentRequirementWidget::SetCarrier(UObject* ProvidedCarrier)
{
	Carrier = Cast<UGoodRequirementCarrier>(ProvidedCarrier);
}

void UUnitTypeEquipmentRequirementWidget::RefreshData()
{
	GoodNameTextBlock->SetText(FText::FromName(Carrier->GetGoodName()));
	AmountTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->GetRequirement())));
}