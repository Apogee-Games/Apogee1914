#pragma once
#include "Administration/Descriptions/CountryProvinces.h"
#include "Administration/Descriptions/ProvinceDescription.h"
#include "Administration/Descriptions/Country/CountryDescription.h"
#include "Administration/Descriptions/Law/LawsGroup.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "Economics/Description/ResourceDescription.h"
#include "Economics/Description/StrataDescription.h"
#include "Economics/Description/Buildings/BuildingDescription.h"
#include "Economics/Description/Goods/GoodDescription.h"
#include "Engine/DataAsset.h"
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
	TArray<UStrataDescription*> StrataDescriptions;
	
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
	UTexture2D* ProvincesMapTexture;

	UPROPERTY(EditDefaultsOnly)
	UTextureRenderTarget2D* ProvincesIdsLookUpTexture;
	
	UPROPERTY(EditDefaultsOnly)
	UTextureRenderTarget2D* ProvincesColorsLookUpTexture;

	UPROPERTY(EditDefaultsOnly)
	UTextureRenderTarget2D* MiniMapTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	FDateTime StartTime = FDateTime(1914, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	int32 MaxTimeSpeed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	float SpeedMultiplier = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Maps | Selection")
	FColor SelectionHighlight = FColor(75, 75, 150);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Maps | Relation")
	FColor NonAlignedCountryColor = FColor(10, 10, 10);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Maps | Relation")
	FColor NonAlliedCountryColor = FColor(200, 200, 200);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Maps | Relation")
	TMap<ERelationType, FColor> RelationsColors = {
		{ERelationType::Neutral, FColor(30, 30, 30)},
		{ERelationType::NonAggressionPact, FColor(0, 30, 30)},
		{ERelationType::War, FColor(150, 10, 10)},
		{ERelationType::DefencivePact, FColor(30, 150, 30)},
		{ERelationType::Allied, FColor(30, 100, 150)}
	};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Maps | Relation")
	TMap<ERelationType, FColor> MiniMapColors = {
		{ERelationType::Neutral, FColor(150, 150, 150)},
		{ERelationType::NonAggressionPact, FColor(150, 200, 150)},
		{ERelationType::War, FColor(200, 10, 10)},
		{ERelationType::DefencivePact, FColor(0, 200, 200)},
		{ERelationType::Allied, FColor(0, 0, 200)}
	};
	
};
