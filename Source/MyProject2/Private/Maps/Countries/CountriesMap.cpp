
#include "Maps/Countries/CountriesMap.h"

#include "MyGameInstance.h"
#include "Administration/Managers/ProvinceManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/Countries/CountryMapUpdater.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Maps/Precalculations/Distances/DistancesMap.h"
#include "Utils/TextureUtils.h"

void UCountriesMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(Cast<UMyGameInstance>(GetGameInstance())->ProvinceManagerClass);
	GetGameInstance()->GetSubsystem<UProvinceManager>()->AddProvinceControllingCountryObserver(this);
}

void UCountriesMap::SetScenario(UScenario* Scenario)
{
	CountriesMapTexture = Scenario->CountriesMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(CountriesMapTexture);
	UpdateCountriesMapColors(GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces());
}

void UCountriesMap::UpdateCountriesMapColors(const TArray<UProvince*>& Provinces) const
{
	TArray<FRunnableThread*> Threads;

	FColor* CountriesColors = FTextureUtils::GetPixels(CountriesMapTexture, LOCK_READ_WRITE);
	
	for (const auto& Province: Provinces)
	{
		Threads.Add(UpdateCountryColor(Province, CountriesColors));
	}
	
	for (const auto& Thread: Threads)
	{
		Thread->WaitForCompletion();
	}
	
	FTextureUtils::UnlockPixels(CountriesMapTexture);
    
    CountriesMapTexture->UpdateResource();
}

void UCountriesMap::UpdateAllCountriesMapColors()
{
}

void UCountriesMap::ProvinceHasNewControllingCountry(UProvince* Province)
{
	UpdateCountriesMapColors({Province});
}

void UCountriesMap::CountryDistancesWereUpdated(const TArray<UProvince*>& Provinces)
{
	UpdateAllCountriesMapColors(); // TODO: Is this correct? :)
}

FRunnableThread* UCountriesMap::UpdateCountryColor(UProvince* Province, FColor* CountriesColor) const
{
	const TArray<int32>& PixelsToUpdate = GetGameInstance()->GetSubsystem<UProvincesMap>()->GetProvincePositions(Province->GetId());
	const TArray<int32>& Distances = GetGameInstance()->GetSubsystem<UDistancesMap>()->GetCountriesDistances();
	FCountryMapUpdater* Updater = new FCountryMapUpdater(CountriesColor, PixelsToUpdate, Province, Distances, SizeVector, CrossLineWidth);
	return FRunnableThread::Create(Updater, *Province->GetName().ToString());	
}
