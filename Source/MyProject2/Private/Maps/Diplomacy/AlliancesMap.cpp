#include "Maps/Diplomacy/AlliancesMap.h"

#include "MyGameInstance.h"
#include "Administration/Instances/Province.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Utils/TextureUtils.h"

void UAlliancesMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(Cast<UMyGameInstance>(GetGameInstance())->RelationshipsManagerClass);
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->AddAllianceCreationObserver(this);
}

void UAlliancesMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UAlliancesMap::UpdateMap()
{
	TArray<UProvince*> Provinces = GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces();
	UProvincesMap* ProvincesMap = GetGameInstance()->GetSubsystem<UProvincesMap>();

	FColor* Colors = FTextureUtils::GetPixels(AlliancesMapTexture, LOCK_READ_WRITE);
	
	for (const auto& Province: Provinces)
	{
		UCountry* Country = Province->GetCountryController();
		FColor Color = GetColor(Country);

		for (const auto& Position: ProvincesMap->GetProvincePositions(Province->GetId()))
		{
			Colors[Position] = Color;
		}
	}

	FTextureUtils::UnlockPixels(AlliancesMapTexture);
	AlliancesMapTexture->UpdateResource();
}

void UAlliancesMap::AllianceWasCreated(UAlliance* Alliance)
{
	UpdateMap();
}

void UAlliancesMap::Clear()
{
	AlliancesMapTexture = nullptr;
}

void UAlliancesMap::Init(UScenario* Scenario)
{
	AlliancesMapTexture = Scenario->AlliancesMapTexture;
}

FColor UAlliancesMap::GetColor(UCountry* Country)
{
	if (Country->IsNonAligned()) return NonAlignedCountryColor;
	if (!Country->IsInAlliance()) return NonAlliedCountryColor;
	return Country->GetAlliance()->GetColor();
}
