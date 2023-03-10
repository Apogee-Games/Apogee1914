#pragma once
#include "Country.h"
#include "ProvincePopulation.h"
#include "ProvinceResources.h"
#include "MyProject2/Administration/Descriptions/ProvinceDescription.h"
#include "MyProject2/Administration/Descriptions/TerrainDescription.h"
#include "MyProject2/Economics/Instances/Public/Building.h"
#include "Province.generated.h"

UCLASS()
class UProvince : public UObject 
{
	GENERATED_BODY()
public:
	UProvince();

	void Init(FProvinceDescription* ProvinceDescription, const UDataTable* TerrainDT, const UDataTable* FactoryDT, const UDataTable* ResourcesDescriptions);

	const FColor& GetId() const;

	UCountry* GetOwnerCountry() const;

	UCountry* GetCountryController() const;
	
	void TakeControl(UCountry* Country);

	void Conquer(UCountry* Country);

	const FName& GetStateId() const;
	
	const FName& GetName();

	const UProvincePopulation* GetPopulation() const;

	const FTerrainDescription* GetTerrain() const;

	UProvinceResources* GetResources() const;

	void AddBuilding(UBuilding* Building);

	void RemoveBuilding(UBuilding* Building);

	const TArray<UBuilding*>& GetBuildings() const;

	//TODO: Tie resource logic to building logic
	
private:
	
	FColor Id;

	FName Name;

	UPROPERTY()
	UCountry* OwnerCountry;

	UPROPERTY()
	UCountry* ControllerCountry;

	FName StateId;
	
	UPROPERTY()
	UProvincePopulation* Population;
	
	FTerrainDescription* Terrain;

	UPROPERTY()
	UProvinceResources* Resources;
	
	UPROPERTY()
	TArray<UBuilding*> Buildings;
};
