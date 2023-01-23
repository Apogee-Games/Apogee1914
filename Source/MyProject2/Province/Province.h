#pragma once
#include "Descriptions/ProvinceDescription.h"
#include "Descriptions/TerrainDescription.h"
#include "MyProject2/Economics/ProvinceFactory.h"
#include "Instances/ProvincePopulation.h"
#include "Province.generated.h"

UCLASS()
class UProvince : public UObject 
{
	GENERATED_BODY()
public:
	UProvince();

	void Init(FProvinceDescription* ProvinceDescription, const UDataTable* TerrainDT, const UDataTable* FactoryDT);

	const FColor& GetId() const;

	const FString& GetCountryTag() const;

	const FString& GetStateId() const;
	
	const FString& GetProvinceName() const;

	const UProvincePopulation* GetPopulation() const;

	const FTerrainDescription* GetTerrain() const;

	const TMap<FString, int> GetResources() const;
	
private:
	
	FColor Id;

	FString ProvinceName;

	FString CountryTag;

	FString StateId;

	UPROPERTY()
	UProvincePopulation* Population;
	
	FTerrainDescription* Terrain;
	
	TMap<FString, int> Resources;
	
	UPROPERTY() // To prevent from garbage collecting all the factories :)
	TArray<UProvinceFactory*> Factories; 
};
