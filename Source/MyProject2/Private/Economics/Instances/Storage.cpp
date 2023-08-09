#include "Economics/Instances/Storage.h"
#include "Economics/Description/Goods/GoodDescription.h"

void UStorage::Init(EStorageType ProvidedType)
{
	Type = ProvidedType;
}

void UStorage::Init(const FName& StrataType)
{
	Type = StrataTypeToStorageType[StrataType];
}

void UStorage::Supply(UGoodDescription* Good, const int32 Amount)
{
	AddGoodIfNotPresent(Good);
	Goods[Good]->Supply(Amount);
	OnStorageGoodUpdated.Broadcast(Type, Goods[Good]);
}

float UStorage::Estimate(UGoodDescription* Good, const int32 Amount)
{
	AddGoodIfNotPresent(Good);
	return FMath::Min(Goods[Good]->GetAmount(), Amount);
}

float UStorage::GetGoodAmount(UGoodDescription* Good) const
{
	return !Goods.Contains(Good) ? 0 : Goods[Good]->GetAmount(); 
}

float UStorage::Demand(UGoodDescription* Good, const int32 Amount)
{
	AddGoodIfNotPresent(Good);
	const int32 CanProvide = Goods[Good]->Demand(Amount);
	OnStorageGoodUpdated.Broadcast(Type, Goods[Good]);
	return CanProvide;
}

EStorageType UStorage::GetType() const
{
	return Type;
}

void UStorage::AddGoodIfNotPresent(UGoodDescription* Good)
{
	if (!Goods.Contains(Good))
	{
		UStoredGood* StoredGood = NewObject<UStoredGood>(this);
		StoredGood->Init(Good, 0, this);
		Goods.Add(Good, StoredGood);
	}
}
