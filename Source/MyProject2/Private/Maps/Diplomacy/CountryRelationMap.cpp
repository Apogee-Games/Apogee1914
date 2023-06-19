#include "Maps/Diplomacy/CountryRelationMap.h"
#include "MyGameInstance.h"
#include "Administration/Managers/CountriesManager.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Utils/TextureUtils.h"


void UCountryRelationMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(Cast<UMyGameInstance>(GetGameInstance())->RelationshipsManagerClass);
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->AddWarDeclarationObserver(this);
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->AddAllianceCreationObserver(this);
}

void UCountryRelationMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UCountryRelationMap::UpdateMap()
{
	// TODO: Check getters :)

	FColor* Colors = FTextureUtils::GetPixels(CountryRelationMap, LOCK_READ_WRITE);

	const TArray<UProvince*>& Provinces = GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces(); 
	UProvincesMap* ProvincesMap = GetGameInstance()->GetSubsystem<UProvincesMap>();

	UCountry* Germany = GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry(GermanyDescription);
	
	for (const auto& Province: Provinces)
	{
		// TODO: Add for each country :)
		
		FColor Color = ColorsMapping[Germany->GetRelation(Province->GetCountryController())];
		for (const int32 Position: ProvincesMap->GetProvincePositions(Province->GetId()))
		{
			Colors[Position] = Color;
		}
	}

	FTextureUtils::UnlockPixels(CountryRelationMap);
	
	CountryRelationMap->UpdateResource();
}

void UCountryRelationMap::WarWasDeclared(UWar* War)
{
	UpdateMap();
}

void UCountryRelationMap::AllianceWasCreated(UAlliance* Alliance)
{
	UpdateMap();
}

ELoadStage UCountryRelationMap::GetLoadStage()
{
	return ELoadStage::CountryRelationMap;
}

void UCountryRelationMap::Clear()
{
	CountryRelationMap = nullptr;
}

void UCountryRelationMap::Init(UScenario* Scenario)
{
	CountryRelationMap = Scenario->CountryRelationMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(CountryRelationMap);
}
