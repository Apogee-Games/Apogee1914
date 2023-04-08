#pragma once
#include "SkillDescription.h"
#include "ProfessionDescription.generated.h"

UCLASS()
class UProfessionDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	
	UPROPERTY(EditDefaultsOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly)
	TMap<USkillDescription*, float> BaseSkillsValues; // TODO: Make use of it :)
};
