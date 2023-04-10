

#include "Widgets/Military/Carriers/GoodNeedCarrier.h"

void UGoodNeedCarrier::Init(UUnitSupplyNeeds* ProvidedUnitSupplyNeed, UGoodDescription* ProvidedGood)
{
	UnitSupplyNeeds = ProvidedUnitSupplyNeed;
	Good = ProvidedGood;
}

float UGoodNeedCarrier::GetGoodSupply() const
{
	return UnitSupplyNeeds->GetGoodSupply(Good);
}

float UGoodNeedCarrier::GetGoodRequirements() const
{
	return UnitSupplyNeeds->GetGoodRequirements(Good);
}

const FText& UGoodNeedCarrier::GetGoodName() const
{
	return Good->NameText;
}
