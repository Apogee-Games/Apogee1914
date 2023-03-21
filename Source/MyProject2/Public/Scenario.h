#pragma once
#include "Engine/DataTable.h"
#include "Scenario.generated.h"

UCLASS()
class UScenario: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FName ScenarioName;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* CountryDescriptionDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ProvinceDescriptionDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* TerrainDescriptionDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ResourcesDescriptionDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* StateDescriptionDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* GoodDescriptionDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* StrataDescriptionDataTable;	
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* UnitsDescriptionDataTable;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* BuildingsDescriptionDataTable;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* EventsDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* PeoplesDescriptions;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* SelectionMapTexture;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ProvincesMapTexture;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* OutlinesMapTexture;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* FlagsMapTexture;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CountriesMapTexture;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CountryRelationMapTexture;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* AlliancesMapTexture;
};
