#pragma once
#include "PersonDescription.h"
#include "ProfessionGroup.generated.h"

UCLASS()
class UProfessionGroup: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<UPersonDescription*> PeopleDescriptions;
};
