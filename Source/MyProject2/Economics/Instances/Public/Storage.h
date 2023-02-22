#pragma once
#include "MyProject2/Economics/Description/GoodDescription.h"

#include "Storage.generated.h"

UCLASS()
class UStorage: public UObject
{
	GENERATED_BODY()
public:

	void Supply(const FName& Good, const int32 Amount);

	int Estimate(const FName& Good, const int32 Amount);

	int GetGoodAmount(const FName& Good) const;
	
	int Demand(const FName& Good, const int32 Amount);

private:
	TMap<FName, int32> Goods;
};
