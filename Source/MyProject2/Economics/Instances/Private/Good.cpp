
#include "MyProject2/Economics/Instances/Public/Good.h"

void UGood::Init(FName ProvidedGoodName, int32 ProvidedAmount, UStorage* ProvidedStorage)
{
	GoodName = ProvidedGoodName;
	Amount = ProvidedAmount;
	Storage = ProvidedStorage;
}

void UGood::Supply(int32 SuppliedAmount)
{
	Amount += SuppliedAmount;
}

int32 UGood::GetAmount()
{
	return Amount;
}

int32 UGood::Demand(int32 DemandedAmount)
{
	const int PossibleAmount = FMath::Min(Amount, DemandedAmount);
	Amount -= PossibleAmount;
	return PossibleAmount;
}

const FName& UGood::GetGoodName() const
{
	return GoodName;
}

UStorage* UGood::GetStorage() const
{
	return Storage;
}
