
#include "Widgets/Economics/Buildings/Creation/GoodProductionWidget.h"

void UGoodProductionWidget::SetCarrier(UObject* ProvidedCarrier)
{
	Carrier = Cast<UGoodProductionCarrier>(ProvidedCarrier);
}

void UGoodProductionWidget::RefreshData()
{
	GoodNameTextBlock->SetText(FText::FromName(Carrier->GetGoodName()));
	ProductionAmountTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->GetGoodProduction())));
}
