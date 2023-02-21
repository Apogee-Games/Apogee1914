#pragma once
#include "GoodBalance.h"
#include "Market.generated.h"

UCLASS()
class UMarket : public UObject
{
	GENERATED_BODY()
public:
	UMarket();

	int AddDemand(const FGoodDescription* GoodDescription, int Amount);
	int AddSupply(const FGoodDescription* GoodDescription, int Amount);

	TArray<TPair<FString, int>> GetMostDemanded();
private:

	
	UPROPERTY()
	TMap<FString, UGoodBalance*> Balances;

	UPROPERTY()
	TMap<FString, UGoodBalance*> Potential;
	
};
