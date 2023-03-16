
#include "Maps/Countries/CountriesMap.h"

#include "MyGameInstance.h"
#include "Administration/Managers/ProvinceManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/Countries/CountryMapUpdater.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Maps/Precalculations/Distances/DistancesMap.h"
#include "Utils/TextureUtils.h"

bool UCountriesMap::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UCountriesMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CountriesMapTexture = GetWorld()->GetGameInstance<UMyGameInstance>()->ActiveScenario->CountriesMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(CountriesMapTexture);
	GetWorld()->GetSubsystem<UDistancesMap>()->RegisterOnFullInitializationAction(this, &UCountriesMap::UpdateAllCountriesMapColors);
	GetWorld()->GetSubsystem<UProvinceManager>()->AddProvinceControllingCountryObserver(this);
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
	UpdateCountriesMapColors(GetWorld()->GetSubsystem<UProvinceManager>()->GetAllProvinces());
}

void UCountriesMap::ProvinceHasNewControllingCountry(UProvince* Province)
{
	UpdateCountriesMapColors({Province});
}

void UCountriesMap::CountryDistancesWereUpdated(const TArray<UProvince*>& Provinces)
{
	UpdateAllCountriesMapColors();
}

FRunnableThread* UCountriesMap::UpdateCountryColor(UProvince* Province, FColor* CountriesColor) const
{
	const TArray<int32>& PixelsToUpdate = GetWorld()->GetSubsystem<UProvincesMap>()->GetProvincePositions(Province->GetId());
	const TArray<int32>& Distances = GetWorld()->GetSubsystem<UDistancesMap>()->GetCountriesDistances();
	FCountryMapUpdater* Updater = new FCountryMapUpdater(CountriesColor, PixelsToUpdate, Province, Distances, SizeVector, CrossLineWidth);
	return FRunnableThread::Create(Updater, *Province->GetName().ToString());	
}
