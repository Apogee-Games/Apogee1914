#pragma once
#include "StateDescription.h"
#include "TerrainDescription.h"
#include "Country/CountryDescription.h"
#include "ProvinceDescription.generated.h"

class UResourceDescription;

UCLASS()
class UProvinceDescription : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FColor Color;
	
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	
	UPROPERTY(EditDefaultsOnly)
	UCountryDescription* Country;
	
	UPROPERTY(EditDefaultsOnly)
	UStateDescription* State;
	
	UPROPERTY(EditDefaultsOnly)
	UTerrainDescription* Terrain;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<UResourceDescription*, int32> Resources;
	
	UPROPERTY(EditDefaultsOnly)
	int32 Population;
};
