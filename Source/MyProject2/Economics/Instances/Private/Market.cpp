#include "../Public/Market.h"


UMarket::UMarket()
{
}

int UMarket::AddDemand(const FGoodDescription* GoodDescription, const int Amount)
{
	const FString GoodName = GoodDescription->GoodName;
	// If Good not in market
	UGoodBalance* GoodBalance = Balances.FindRef(GoodName);
	if ( GoodBalance == nullptr)
	{
		GoodBalance = NewObject<UGoodBalance>();
		GoodBalance->Init(GoodDescription);
		Balances.Add(GoodName, GoodBalance);
	}
	const int Demand = GoodBalance->Demand(Amount);
	if(GoodBalance->GetSupply() == 0 && Demand == 0) Balances.Remove(GoodName);
	return Demand;
	
}


int UMarket::AddSupply(const FGoodDescription* GoodDescription, const int Amount)
{
	const FString GoodName = GoodDescription->GoodName;
	// If Good not in market
	UGoodBalance* GoodBalance = Balances.FindRef(GoodName);
	if ( GoodBalance == nullptr)
	{
		GoodBalance = NewObject<UGoodBalance>();
		GoodBalance->Init(GoodDescription);
		Balances.Add(GoodName, GoodBalance);
	}
	const int Supply = GoodBalance->Supply(Amount);
	if(GoodBalance->GetDemand() == 0 && Supply == 0) Balances.Remove(GoodName);
	return Supply;
	
}

TArray<TPair<FString, int>> UMarket::GetMostDemanded()
{
	TArray<TPair<FString, int>> MostDemanded;

	for(const auto &[Key,Value] : Balances)
	{
		int Balance = Value->GetBalance();
		if(Balance < 0)
		{
			MostDemanded.Add({Key, Balance});
		}
	}
	MostDemanded.HeapSort(
		[](const TPair<FString, int>& p1, const TPair<FString, int>& p2)
		{return p1 > p2;});
	return MostDemanded;
}


