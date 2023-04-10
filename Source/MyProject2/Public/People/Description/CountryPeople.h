#pragma once
#include "ProfessionGroup.h"

#include "CountryPeople.generated.h"

UCLASS()
class UCountryPeople: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TMap<UProfessionDescription*, UProfessionGroup*> ProfessionGroups;
};
