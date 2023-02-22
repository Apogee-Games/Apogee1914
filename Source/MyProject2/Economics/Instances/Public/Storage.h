#pragma once
#include "MyProject2/Economics/Description/GoodDescription.h"

#include "Storage.generated.h"

UCLASS()
class UStorage: public UObject
{
	GENERATED_BODY()
public:

	void Supply(const FName& Good, const int32 Amount);

	int32 Estimate(const FName& Good, const int32 Amount);

	int32 GetGoodAmount(const FName& Good) const;
	
	int32 Demand(const FName& Good, const int32 Amount);

private:
	TMap<FName, int32> Goods;
};
