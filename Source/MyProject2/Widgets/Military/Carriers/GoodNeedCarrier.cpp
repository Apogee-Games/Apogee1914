#include "GoodNeedCarrier.h"


void UGoodNeedCarrier::Init(UUnitSupplyNeeds* ProvidedUnitSupplyNeed, const FName& ProvidedGoodName)
{
	UnitSupplyNeeds = ProvidedUnitSupplyNeed;
	GoodName = &ProvidedGoodName;
}

int32 UGoodNeedCarrier::GetGoodSupply() const
{
	return UnitSupplyNeeds->GetGoodSupply(*GoodName);
}

int32 UGoodNeedCarrier::GetGoodRequirements() const
{
	return UnitSupplyNeeds->GetGoodRequirements(*GoodName);
}

const FName& UGoodNeedCarrier::GetGoodName() const
{
	return *GoodName;
}
