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

	void Init();

private:
	UPROPERTY()
	UMarket* StrataMarket;

	UPROPERTY()
	FName Type; 
	
};