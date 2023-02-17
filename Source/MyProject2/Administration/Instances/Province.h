#pragma once
#include "Country.h"
#include "ProvincePopulation.h"
#include "MyProject2/Administration/Descriptions/ProvinceDescription.h"
#include "MyProject2/Administration/Descriptions/TerrainDescription.h"
#include "MyProject2/Economics/ProvinceFactory.h"
#include "Province.generated.h"

class UUnit;
UCLASS()
class UProvince : public UObject 
{
	GENERATED_BODY()
public:
	UProvince();

	void Init(FProvinceDescription* ProvinceDescription, const UDataTable* TerrainDT, const UDataTable* FactoryDT);

	const FColor& GetId() const;

	UCountry* GetOwnerCountry() const;

	UCountry* GetCountryController() const;
	
	void TakeControl(UCountry* Country);

	void Conquer(UCountry* Country);

	const FString& GetStateId() const;
	
	const FString& GetName();

	const UProvincePopulation* GetPopulation() const;

	const FTerrainDescription* GetTerrain() const;

	const TMap<FString, int> GetResources() const;
	
private:
	
	FColor Id;

	FString Name;

	UPROPERTY()
	UCountry* OwnerCountry;

	UPROPERTY()
	UCountry* ControllerCountry;

	FString StateId;

	TMap<FString, int32> UnitsRenderingPosition;

	UPROPERTY()
	UProvincePopulation* Population;
	
	FTerrainDescription* Terrain;
	
	TMap<FString, int> Resources;
	
	UPROPERTY() // To prevent from garbage collecting all the factories :)
	TArray<UProvinceFactory*> Factories; 
};
