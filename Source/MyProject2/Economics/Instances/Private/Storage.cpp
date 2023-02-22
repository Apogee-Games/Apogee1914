
#include "MyProject2/Economics/Instances/Public/Storage.h"

void UStorage::Supply(const FName& Good, const int32 Amount)
{
	if (!Goods.Contains(Good))
	{
		Goods.Add(Good, 0);
	}
	Goods[Good] += Amount;
}

int UStorage::Estimate(const FName& Good, const int32 Amount)
{
	if (!Goods.Contains(Good))
	{
		Goods.Add(Good, 0);
	}
	return FMath::Min(Goods[Good], Amount);
}

int UStorage::Demand(const FName& Good, const int32 Amount)
{
	if (!Goods.Contains(Good))
	{
		Goods.Add(Good, 0);
	}
	const int CanProvide = FMath::Min(Goods[Good], Amount);
	Goods[Good] -= CanProvide;
	return CanProvide;
}
