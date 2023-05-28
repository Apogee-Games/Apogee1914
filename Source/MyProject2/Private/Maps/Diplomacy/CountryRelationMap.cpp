#include "Maps/Diplomacy/CountryRelationMap.h"
#include "MyGameInstance.h"
#include "Administration/Managers/CountriesManager.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Maps/Diplomacy/CountryRelationMapUpdater.h"
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

	TArray<FRunnableThread*> Threads;

	for (const auto& Province : Provinces)
	{
		FRunnableThread* Thread = UpdateProvince(
			ProvincesMap->GetProvincePositions(Province->GetId()),
			Colors,
			ColorsMapping[Germany->GetRelation(Province->GetCountryController())],
			ToCStr(Province->GetName().ToString())
		);
		Threads.Add(Thread);
	}

	for (const auto& Thread : Threads)
	{
		Thread->WaitForCompletion();
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

void UCountryRelationMap::Clear()
{
	CountryRelationMap = nullptr;
}

void UCountryRelationMap::Init(UScenario* Scenario)
{
	CountryRelationMap = Scenario->CountryRelationMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(CountryRelationMap);
}

FRunnableThread* UCountryRelationMap::UpdateProvince(const TArray<int32>& Positions, FColor* Colors, FColor Color,
                                                     const TCHAR* ProvinceName)
{
	FRunnable* Updater = new FCountryRelationMapUpdater(Positions, Colors, Color);
	return FRunnableThread::Create(Updater, ProvinceName);
}
