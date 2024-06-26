
#include "Widgets/Military/Supply/UnitSupplyNeedWidget.h"

void UUnitSupplyNeedWidget::SetCarrier(UObject* ProvidedCarrier)
{
	Carrier = Cast<UGoodNeedCarrier>(ProvidedCarrier);
}

void UUnitSupplyNeedWidget::RefreshData()
{
	GoodNameTextBlock->SetText(Carrier->GetGoodName());
	GoodSupplyTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->GetGoodSupply())));
	GoodRequirementTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->GetGoodRequirements())));
}
