#include "../Public/Market.h"


UMarket::UMarket()
{
}

int UMarket::AddDemand(const FGoodDescription* GoodDescription, const int AmountOfGood)
{
	UGoodBalance* GoodBalance = GetBalanceInstanceOrElseInit(GoodDescription);
	// Add to demand
	const int Demand = GoodBalance->Demand(AmountOfGood);
	// Delete if not presented in Market (after change of demand)
	CheckBalanceInstance(GoodBalance);
	return Demand;
	
}


int UMarket::AddSupply(const FGoodDescription* GoodDescription, const int AmountOfGood)
{
	UGoodBalance* GoodBalance = GetBalanceInstanceOrElseInit(GoodDescription);
	// Add to supply
	const int Supply = GoodBalance->Supply(AmountOfGood);
	// Delete if not presented at Market (after change of supply)
	CheckBalanceInstance(GoodBalance);
	return Supply;
	
}

TArray<TPair<FName, int>> UMarket::GetSortedDemands()
{
	TArray<TPair<FName, int>> SortedDemands;

	for(const auto &[Key,Value] : Balances)
	{
		int Balance = Value->GetBalance();
		if(Balance < 0)
		{
			SortedDemands.Add({Key, Balance});
		}
	}
	SortedDemands.HeapSort(
		[](const TPair<FName, int>& p1, const TPair<FName, int>& p2)
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



