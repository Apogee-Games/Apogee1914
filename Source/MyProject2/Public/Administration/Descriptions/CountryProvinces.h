#pragma once
#include "ProvinceDescription.h"
#include "CountryProvinces.generated.h"

UCLASS()
class UCountryProvinces: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<UProvinceDescription*> Provinces;
};
