
#include "Widgets/Economics/Buildings/Creation/ResourceConsumptionWidget.h"

void UResourceConsumptionWidget::SetCarrier(UObject* ProvidedCarrier)
{
	Carrier = Cast<UResourceConsumptionCarrier>(ProvidedCarrier);
}

void UResourceConsumptionWidget::RefreshData()
{
	ResourceNameTextBlock->SetText(FText::FromName(Carrier->GetResourceName()));
	UsedAmountTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->GetResourceConsumption())));
}


