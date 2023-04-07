#pragma once
#include "MilitaryBranchDescription.generated.h"

class UUnit;

UCLASS()
class UMilitaryBranchDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;

    UPROPERTY(EditDefaultsOnly)
    FColor Color;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUnit> UnitClass;
};