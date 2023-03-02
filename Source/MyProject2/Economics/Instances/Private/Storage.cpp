
#include "MyProject2/Economics/Instances/Public/Storage.h"

void UStorage::Init(EStorageType ProvidedType)
{
	Type = ProvidedType;
}

void UStorage::Init(const FName& StrataType)
{
	Type = StrataTypeToStorageType[StrataType];
}

void UStorage::Supply(const FName& GoodName, const int32 Amount)
{
	AddGoodIfNotPresent(GoodName);
	Goods[GoodName]->Supply(Amount);
	NotifyGoodUpdate(Type, Goods[GoodName]);
}

int32 UStorage::Estimate(const FName& GoodName, const int32 Amount)
{
	AddGoodIfNotPresent(GoodName);
	return FMath::Min(Goods[GoodName]->GetAmount(), Amount);
}

int32 UStorage::GetGoodAmount(const FName& GoodName) const
{
	return !Goods.Contains(GoodName) ? 0 : Goods[GoodName]->GetAmount(); 
}

int32 UStorage::Demand(const FName& GoodName, const int32 Amount)
{
	AddGoodIfNotPresent(GoodName);
	const int32 CanProvide = Goods[GoodName]->Demand(Amount);
	NotifyGoodUpdate(Type, Goods[GoodName]);
	return CanProvide;
}

EStorageType UStorage::GetType() const
{
	return Type;
}

void UStorage::AddGoodIfNotPresent(const FName& GoodName)
{
	if (!Goods.Contains(GoodName))
	{
		UGood* Good = NewObject<UGood>();
		Good->Init(GoodName, 0, this);
		Goods.Add(GoodName, Good);
	}
}
