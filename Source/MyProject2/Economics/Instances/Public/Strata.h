#pragma once
#include "Market.h"
#include "MyProject2/Economics/Description/StrataDescription.h"
#include "Strata.generated.h"

UCLASS()
class UStrata : public UObject
{
	GENERATED_BODY()

public:
	UStrata();

	void Initialize();
	
	
private:
	UPROPERTY()
	UMarket* StrataMarket;

	UPROPERTY()
	FString Type; 
	
};