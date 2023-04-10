#pragma once

#include "SkillDescription.generated.h"

UCLASS()
class USkillDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	
	UPROPERTY(EditDefaultsOnly)
	FText Description;
};
