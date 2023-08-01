

#include "Economics/Instances/Market.h"

UMarket::UMarket()
{
}

int32 UMarket::AddDemand(UGoodDescription* GoodDescription, const int32 AmountOfGood)
{
	UGoodBalance* GoodBalance = GetBalanceInstanceOrElseInit(GoodDescription);
	// Add to demand
	const int32 Demand = GoodBalance->Demand(AmountOfGood);
	// Delete if not presented in Market (after change of demand)
	CheckBalanceInstance(GoodBalance);
	return Demand;
	
}

int32 UMarket::AddSupply(UGoodDescription* GoodDescription, const int32 AmountOfGood)
{
	UGoodBalance* GoodBalance = GetBalanceInstanceOrElseInit(GoodDescription);
	// Add to supply
	const int32 Supply = GoodBalance->Supply(AmountOfGood);
	// Delete if not presented at Market (after change of supply)
	CheckBalanceInstance(GoodBalance);
	return Supply;
	
}

TArray<TPair<FString, int32>> UMarket::GetSortedDemands()
{
	TArray<TPair<FString, int32>> SortedDemands;

	for(const auto &[GoodName, GoodBalance] : Balances)
	{
		const int32 Balance = GoodBalance->GetBalance();
		if(Balance < 0)
		{
			SortedDemands.Add({GoodName.ToString(), Balance});
		}
	}
	SortedDemands.HeapSort(
		[](const TPair<FString, int32>& p1, const TPair<FString, int32>& p2)
		{
			return p1 > p2;
		});
	return SortedDemands;
}

UGoodBalance* UMarket::GetBalanceInstanceOrElseInit(UGoodDescription* GoodDescription)
{
	
	const FName& GoodName = GoodDescription->Name;
	
	UGoodBalance* GoodBalance = Balances.FindRef(GoodName);
	if ( GoodBalance == nullptr)
	{
		GoodBalance = NewObject<UGoodBalance>(this);
		GoodBalance->Init(GoodDescription);
		Balances.Add(GoodName, GoodBalance);
	}
	return GoodBalance;
}

void UMarket::CheckBalanceInstance(const UGoodBalance* GoodBalance)
{
	const FName GoodName = GoodBalance->GetGoodDescription()->Name;
	if(GoodBalance->GetDemand() == 0 && GoodBalance->GetSupply() == 0) Balances.Remove(GoodName);
}



