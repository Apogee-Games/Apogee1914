#pragma once
#include "GoodBalance.h"
#include "Market.generated.h"

UCLASS()
class UMarket : public UObject
{
	GENERATED_BODY()
public:
	UMarket();

	int AddDemand(const FGoodDescription* GoodDescription, int AmountOfGood);
	int AddSupply(const FGoodDescription* GoodDescription, int AmountOfGood);

	TArray<TPair<FName, int>> GetSortedDemands();
private:

	UGoodBalance* GetBalanceInstanceOrElseInit(const FGoodDescription* GoodDescription);
	void CheckBalanceInstance(const UGoodBalance* GoodBalance);

	
	UPROPERTY()
	TMap<FName, UGoodBalance*> Balances;

	UPROPERTY()
	TMap<FName, UGoodBalance*> Potential;
	
};
