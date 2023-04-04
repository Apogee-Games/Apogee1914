#pragma once
#include "Economics/Description/ResourceDescription.h"
#include "Economics/Description/Buildings/BuildingDescription.h"
#include "Economics/Description/Goods/GoodDescription.h"
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
	TMap<FName, UResourceDescription*> ResourcesDescriptions;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* StateDescriptionDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* StrataDescriptionDataTable;	
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* UnitsDescriptionDataTable;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UBuildingDescription*> BuildingsDescriptions;

	UPROPERTY(EditDefaultsOnly)
	TMap<FName, UGoodDescription*> GoodsDescriptions;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* EventsDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* PeoplesDescriptionsDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ParliamentsDescriptionsDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* IdeologyDescriptionsDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* LawsDescriptionDataTable;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* SongsDescriptionsDataTable;

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

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* IdeologiesMapTexture;
};
