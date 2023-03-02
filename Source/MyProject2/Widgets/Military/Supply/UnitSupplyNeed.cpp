#include "UnitSupplyNeed.h"

void UUnitSupplyNeed::SetCarrier(UObject* ProvidedCarrier)
{
	Carrier = Cast<UGoodNeedCarrier>(ProvidedCarrier);
}

void UUnitSupplyNeed::RefreshData()
{
	GoodNameTextBlock->SetText(FText::FromName(Carrier->GetGoodName()));
	GoodSupplyTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->GetGoodSupply())));
	GoodRequirementTextBlock->SetText(FText::FromString(FString::FromInt(Carrier->GetGoodRequirements())));
}
