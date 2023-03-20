
#include "Maps/Diplomacy/CountryRelationMap.h"

#include "Administration/Managers/CountriesManager.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Utils/TextureUtils.h"


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
	URelationshipsManager* RelationshipsManager = GetGameInstance()->GetSubsystem<URelationshipsManager>();

	UCountry* Germany = GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry("GER");
	
	for (const auto& Province: Provinces)
	{
		// TODO: Add for each country :)
		
		FColor Color = ColorsMapping[RelationshipsManager->GetRelation(Germany, Province->GetCountryController())];
		for (const int32 Position: ProvincesMap->GetProvincePositions(Province->GetId()))
		{
			Colors[Position] = Color;
		}
	}

	FTextureUtils::UnlockPixels(CountryRelationMap);
	
	CountryRelationMap->UpdateResource();
}

void UCountryRelationMap::Clear()
{
	CountryRelationMap = nullptr;
}

void UCountryRelationMap::Init(UScenario* Scenario)
{
	CountryRelationMap = Scenario->CountryRelationMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(CountryRelationMap);
	UpdateMap();
}
