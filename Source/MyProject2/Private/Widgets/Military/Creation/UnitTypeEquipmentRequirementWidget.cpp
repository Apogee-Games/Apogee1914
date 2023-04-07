
#include "Widgets/Military/Creation/UnitTypeEquipmentRequirementWidget.h"

void UUnitTypeEquipmentRequirementWidget::SetCarrier(UObject* ProvidedCarrier)
{
	Carrier = Cast<UGoodRequirementCarrier>(ProvidedCarrier);
}

void UUnitTypeEquipmentRequirementWidget::RefreshData()
{
	GoodNameTextBlock->SetText(Carrier->GetGoodName());
	AmountTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->GetRequirement())));
}
