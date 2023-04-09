#pragma once
#include "Administration/Descriptions/CountryProvinces.h"
#include "Administration/Descriptions/ProvinceDescription.h"
#include "Administration/Descriptions/Country/CountryDescription.h"
#include "Administration/Descriptions/Law/LawsGroup.h"
#include "Economics/Description/ResourceDescription.h"
#include "Economics/Description/Buildings/BuildingDescription.h"
#include "Economics/Description/Goods/GoodDescription.h"
#include "Engine/DataTable.h"
#include "Events/Description/EventDescription.h"
#include "Military/Descriptions/UnitDescription.h"
#include "Music/Description/SongsGroup.h"
#include "People/Description/CountryPeople.h"
#include "Scenario.generated.h"

UCLASS()
class UScenario: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FName ScenarioName;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UCountryDescription*> CountriesDescriptions;

	UPROPERTY(EditDefaultsOnly)
	TMap<UCountryDescription*, UCountryProvinces*> ProvincesDescriptions;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, UResourceDescription*> ResourcesDescriptions;

	UPROPERTY(EditDefaultsOnly)
	TArray<UStateDescription*> StatesDescriptions;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* StrataDescriptionDataTable;	
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UUnitDescription*> UnitDescriptions;

	UPROPERTY(EditDefaultsOnly)
	TArray<UMilitaryBranchDescription*> MilitaryBranches;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UBuildingDescription*> BuildingsDescriptions;

	UPROPERTY(EditDefaultsOnly)
	TMap<FName, UGoodDescription*> GoodsDescriptions;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UEventDescription*> Events;

	UPROPERTY(EditDefaultsOnly)
	TMap<UCountryDescription*, UCountryPeople*> PeopleDescriptions;

	UPROPERTY(EditDefaultsOnly)
	TArray<ULawsGroup*> LawsGroups;

	UPROPERTY(EditDefaultsOnly)
	TArray<USongsGroup*> SongsGroups;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	FDateTime StartTime = FDateTime(1914, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	int32 MaxTimeSpeed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	float SpeedMultiplier = 0.1;
};
