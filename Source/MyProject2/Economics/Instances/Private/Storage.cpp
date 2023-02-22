
#include "MyProject2/Economics/Instances/Public/Storage.h"

void UStorage::Supply(const FName& Good, const int32 Amount)
{
	if (!Goods.Contains(Good))
	{
		Goods.Add(Good, 0);
	}
	Goods[Good] += Amount;
}

int32 UStorage::Estimate(const FName& Good, const int32 Amount)
{
	if (!Goods.Contains(Good))
	{
		Goods.Add(Good, 0);
	}
	return FMath::Min(Goods[Good], Amount);
}

int32 UStorage::GetGoodAmount(const FName& Good) const
{
	return  !Goods.Contains(Good) ? 0 : Goods[Good]; 
}

int32 UStorage::Demand(const FName& Good, const int32 Amount)
{
	if (!Goods.Contains(Good))
	{
		Goods.Add(Good, 0);
	}
	const int32 CanProvide = FMath::Min(Goods[Good], Amount);
	Goods[Good] -= CanProvide;
	return CanProvide;
}
