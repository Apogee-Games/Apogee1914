#pragma once
#include "GoodDescription.h"
#include "CookedGoodDescription.generated.h"

UCLASS()
class UCookedGoodDescription : public UGoodDescription
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TMap<UGoodDescription*, float> GoodsRequirements;

	UPROPERTY(EditDefaultsOnly)
	float Cost;
};