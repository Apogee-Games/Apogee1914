

#include "Economics/Instances/Market.h"

UMarket::UMarket()
{
}

int32 UMarket::AddDemand(const FGoodDescription* GoodDescription, const int32 AmountOfGood)
{
	UGoodBalance* GoodBalance = GetBalanceInstanceOrElseInit(GoodDescription);
	// Add to demand
	const int32 Demand = GoodBalance->Demand(AmountOfGood);
	// Delete if not presented in Market (after change of demand)
	CheckBalanceInstance(GoodBalance);
	return Demand;
	
}


int32 UMarket::AddSupply(const FGoodDescription* GoodDescription, const int32 AmountOfGood)
{
	UGoodBalance* GoodBalance = GetBalanceInstanceOrElseInit(GoodDescription);
	// Add to supply
	const int32 Supply = GoodBalance->Supply(AmountOfGood);
	// Delete if not presented at Market (after change of supply)
	CheckBalanceInstance(GoodBalance);
	return Supply;
	
}

TArray<TPair<FName, int32>> UMarket::GetSortedDemands()
{
	TArray<TPair<FName, int32>> SortedDemands;

	for(const auto &[GoodName, GoodBalance] : Balances)
	{
		const int32 Balance = GoodBalance->GetBalance();
		if(Balance < 0)
		{
			SortedDemands.Add({GoodName, Balance});
		}
	}
	SortedDemands.HeapSort(
		[](const TPair<FName, int32>& p1, const TPair<FName, int32>& p2)
		{return p1 > p2;});
	return SortedDemands;
}

UGoodBalance* UMarket::GetBalanceInstanceOrElseInit(const FGoodDescription* GoodDescription)
{
	
	const FName& GoodName = GoodDescription->GoodName;
	
	UGoodBalance* GoodBalance = Balances.FindRef(GoodName);
	if ( GoodBalance == nullptr)
	{
		GoodBalance = NewObject<UGoodBalance>();
		GoodBalance->Init(GoodDescription);
		Balances.Add(GoodName, GoodBalance);
	}
	return GoodBalance;
}

void UMarket::CheckBalanceInstance(const UGoodBalance* GoodBalance)
{
	const FName GoodName = GoodBalance->GetGoodDescription()->GoodName;
	if(GoodBalance->GetDemand() == 0 && GoodBalance->GetSupply() == 0) Balances.Remove(GoodName);
}



