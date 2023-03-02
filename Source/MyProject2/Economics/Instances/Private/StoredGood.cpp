
#include "MyProject2/Economics/Instances/Public/StoredGood.h"

void UStoredGood::Init(FName ProvidedGoodName, int32 ProvidedAmount, UStorage* ProvidedStorage)
{
	GoodName = ProvidedGoodName;
	Amount = ProvidedAmount;
	Storage = ProvidedStorage;
}

void UStoredGood::Supply(int32 SuppliedAmount)
{
	Amount += SuppliedAmount;
}

int32 UStoredGood::GetAmount()
{
	return Amount;
}

int32 UStoredGood::Demand(int32 DemandedAmount)
{
	const int PossibleAmount = FMath::Min(Amount, DemandedAmount);
	Amount -= PossibleAmount;
	return PossibleAmount;
}

const FName& UStoredGood::GetGoodName() const
{
	return GoodName;
}

UStorage* UStoredGood::GetStorage() const
{
	return Storage;
}
