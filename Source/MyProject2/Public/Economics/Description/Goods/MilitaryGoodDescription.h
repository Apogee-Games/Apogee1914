#pragma once
#include "CookedGoodDescription.h"
#include "MilitaryGoodDescription.generated.h"

UCLASS()
class UMilitaryGoodDescription : public UCookedGoodDescription
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	float Attack;

	UPROPERTY(EditDefaultsOnly)
	float Defence;
};