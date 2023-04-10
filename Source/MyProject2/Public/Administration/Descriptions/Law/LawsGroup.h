#pragma once
#include "LawsSubgroup.h"
#include "LawsGroup.generated.h"

UCLASS()
class ULawsGroup: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	FCountriesConditions CountriesConditions;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<ULawsSubgroup*> Subgroups;
};
