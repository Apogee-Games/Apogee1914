#pragma once
#include "GoodDescription.h"
#include "MilitaryGoodDescription.generated.h"

UCLASS()
class UMilitaryGoodDescription : public UGoodDescription
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	float Attack;

	UPROPERTY(EditDefaultsOnly)
	float Defence;
};