#pragma once
#include "GoodBalance.h"
#include "Market.generated.h"

UCLASS()
class UMarket : public UObject
{
	GENERATED_BODY()
	
public:
	UMarket();

	int32 AddDemand(UGoodDescription* GoodDescription, int32 AmountOfGood);
	
	int32 AddSupply(UGoodDescription* GoodDescription, int32 AmountOfGood);

	TArray<TPair<FName, int32>> GetSortedDemands();
	
private:
	UGoodBalance* GetBalanceInstanceOrElseInit(UGoodDescription* GoodDescription);
	
	void CheckBalanceInstance(const UGoodBalance* GoodBalance);
	
	UPROPERTY()
	TMap<FName, UGoodBalance*> Balances;

	UPROPERTY()
	TMap<FName, UGoodBalance*> Potential;
	
};
