
#include "Widgets/Economics/Buildings/Creation/GoodConsumptionWidget.h"

void UGoodConsumptionWidget::SetCarrier(UObject* ProvidedCarrier)
{
	Carrier = Cast<UGoodConsumptionCarrier>(ProvidedCarrier);
}

void UGoodConsumptionWidget::RefreshData()
{
	GoodNameTextBlock->SetText(FText::FromName(Carrier->GetGoodName()));
	UsedAmountTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->GetGoodConsumption())));
}
