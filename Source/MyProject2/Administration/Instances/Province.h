#pragma once
#include "ProvincePopulation.h"
#include "MyProject2/Administration/Descriptions/ProvinceDescription.h"
#include "MyProject2/Administration/Descriptions/TerrainDescription.h"
#include "MyProject2/Economics/ProvinceFactory.h"
#include "Province.generated.h"

UCLASS()
class UProvince : public UObject 
{
	GENERATED_BODY()
public:
	UProvince();

	void Init(FProvinceDescription* ProvinceDescription, const UDataTable* TerrainDT, const UDataTable* FactoryDT);

	const FColor& GetId() const;

	const FString& GetOwnerCountryTag() const;

	const FString& GetControllerCountryTag() const;

	void TakeControl(const FString& CountryTag);

	void Conquer(const FString& CountryTag);
	
	const FString& GetStateId() const;
	
	const FString& GetName();

	const UProvincePopulation* GetPopulation() const;

	const FTerrainDescription* GetTerrain() const;

	const TMap<FString, int> GetResources() const;
	
private:
	
	FColor Id;

	FString Name;

	FString OwnerCountryTag;

	FString ControllerCountryTag;

	FString StateId;

	TMap<FString, int32> UnitsRenderingPosition;

	UPROPERTY()
	UProvincePopulation* Population;
	
	FTerrainDescription* Terrain;
	
	TMap<FString, int> Resources;
	
	UPROPERTY() // To prevent from garbage collecting all the factories :)
	TArray<UProvinceFactory*> Factories; 
};
