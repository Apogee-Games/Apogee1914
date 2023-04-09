#pragma once
#include "ProvincePopulation.h"
#include "ProvinceResources.h"
#include "Administration/Descriptions/ProvinceDescription.h"
#include "Administration/Descriptions/TerrainDescription.h"
#include "Economics/Instances/Buildings/Building.h"
#include "Province.generated.h"

class UUnit;
class UCountry;

UCLASS()
class UProvince : public UObject 
{
	GENERATED_BODY()
public:
	UProvince();

	void Init(UProvinceDescription* ProvinceDescription);

	const FColor& GetId() const;

	UCountry* GetOwnerCountry() const;

	UCountry* GetCountryController() const;
	
	void TakeControl(UCountry* Country);

	void Conquer(UCountry* Country);

	UStateDescription* GetState() const;
	
	const FText& GetName();

	const UProvincePopulation* GetPopulation() const;

	UTerrainDescription* GetTerrain() const;

	UProvinceResources* GetResources() const;

	void AddBuilding(UBuilding* Building);

	void RemoveBuilding(UBuilding* Building);

	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);

	const TArray<UUnit*>& GetUnits() const;

	const TArray<UBuilding*>& GetBuildings() const;

	//TODO: Tie resource logic to building logic
	
private:
	FColor Id;

	FText Name;

	UPROPERTY()
	UCountry* OwnerCountry;

	UPROPERTY()
	UCountry* ControllerCountry;

	UPROPERTY()
	UStateDescription* State;
	
	UPROPERTY()
	UProvincePopulation* Population;

	UPROPERTY()
	UTerrainDescription* Terrain;

	UPROPERTY()
	UProvinceResources* Resources;
	
	UPROPERTY()
	TArray<UBuilding*> Buildings;

	UPROPERTY()
	TArray<UUnit*> Units;
};
