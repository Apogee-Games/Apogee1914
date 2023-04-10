#pragma once
#include "ProfessionDescription.h"
#include "SkillDescription.h"
#include "PersonDescription.generated.h"

class UCountryDescription;

UCLASS()
class UPersonDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Image;
	
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	UCountryDescription* Country;
	
	UPROPERTY(EditDefaultsOnly)
	FDateTime DataOfBirth;

	UPROPERTY(EditDefaultsOnly)
	TMap<USkillDescription*, float> Skills;

	UPROPERTY(EditDefaultsOnly)
	TArray<UProfessionDescription*> Professions;
};