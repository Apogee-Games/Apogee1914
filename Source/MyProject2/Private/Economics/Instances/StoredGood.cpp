

#include "Economics/Instances/StoredGood.h"

void UStoredGood::Init(UGoodDescription* ProvidedGood, int32 ProvidedAmount, UStorage* ProvidedStorage)
{
	Good = ProvidedGood;
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

const FText& UStoredGood::GetGoodName() const
{
	return Good->NameText;
}

UStorage* UStoredGood::GetStorage() const
{
	return Storage;
}
