#include "Maps/Diplomacy/AlliancesMap.h"

#include "MyGameInstance.h"
#include "Administration/Instances/Province.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Maps/Diplomacy/AllianceMapUpdater.h"
#include "Utils/TextureUtils.h"

void UAlliancesMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(Cast<UMyGameInstance>(GetGameInstance())->RelationshipsManagerClass);
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->AddAllianceCreationObserver(this);
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->AddAllianceMembersObserver(this);
}

void UAlliancesMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UAlliancesMap::UpdateMap() const 
{
	TArray<FRunnableThread*> Threads;

	FColor* AlliancesColors = FTextureUtils::GetPixels(AlliancesMapTexture, LOCK_READ_WRITE);
	TArray<UProvince*> Provinces = GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces();
	
	for (const auto& Province: Provinces)
	{
		Threads.Add(UpdateAllianceColor(Province, AlliancesColors));
	}
	
	for (const auto& Thread: Threads)
	{
		Thread->WaitForCompletion();
	}
	
	FTextureUtils::UnlockPixels(AlliancesMapTexture);
	
	AlliancesMapTexture->UpdateResource();
	
}

void UAlliancesMap::AllianceWasCreated(UAlliance* Alliance)
{
	UpdateMap();
}

void UAlliancesMap::CountryHasJoinedAlliance(UCountry* Country)
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

FRunnableThread* UAlliancesMap::UpdateAllianceColor(UProvince* Province, FColor* AlliancesColor) const
{
	const TArray<int32>& PixelsToUpdate = GetGameInstance()->GetSubsystem<UProvincesMap>()->GetProvincePositions(Province->GetId());
	FAllianceMapUpdater* Updater = new FAllianceMapUpdater(AlliancesColor, PixelsToUpdate, Province,NonAlignedCountryColor,NonAlliedCountryColor);
	return FRunnableThread::Create(Updater, *Province->GetName().ToString());	
}
