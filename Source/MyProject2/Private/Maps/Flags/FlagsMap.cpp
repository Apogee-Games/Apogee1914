
#include "Maps/Flags/FlagsMap.h"

#include "MyGameInstance.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/Flags/FlagBoxUpdater.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Utils/TextureUtils.h"

void UFlagsMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(Cast<UMyGameInstance>(GetGameInstance())->BoxesMapClass);
	GetGameInstance()->GetSubsystem<UBoxesMap>()->AddBoxObserver(this);
}

void UFlagsMap::Tick()
{
	if (IsUpdated)
	{
		FlagsMapTexture->UpdateResource();
		IsUpdated = false;
	}
}

void UFlagsMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UFlagsMap::UpdateAllBoxes()
{
	UpdateBoxes(GetGameInstance()->GetSubsystem<UBoxesMap>()->GetBoxes());
}

FRunnableThread* UFlagsMap::UpdateBox(const TSharedPtr<FProvincesBox>& Box, FColor* FlagsColors, const FColor* CountryFlagColor, const FVector2d& CountryFlagColorSizeVector)
{
	const UProvincesMap* ProvincesMap = GetGameInstance()->GetSubsystem<UProvincesMap>();
	FRunnable* Runnable = new FFlagBoxUpdater(Box, ProvincesMap, FlagsColors, CountryFlagColor, CountryFlagColorSizeVector);
	return FRunnableThread::Create(Runnable, *Box->GetCountry()->GetTag().ToString());
}

const FColor* UFlagsMap::GetCountryFlagColors(UCountry* Country)
{
	if (!CountriesFlagColors.Contains(Country))
	{
		CountriesFlagColorsCount.Add(Country, 0);
		CountriesFlagColors.Add(Country, FTextureUtils::GetPixels(Country->GetFlag(), LOCK_READ_ONLY));
	}
	CountriesFlagColorsCount[Country]++;
	return CountriesFlagColors[Country];
}

void UFlagsMap::UnlockAllCountriesFlagColors()
{
	for (const auto& [Country, CountryColors]: CountriesFlagColors)
	{
		FTextureUtils::UnlockPixels(Country->GetFlag());
	}
	CountriesFlagColorsCount.Empty();
	CountriesFlagColors.Empty();
}

void UFlagsMap::Clear()
{
	FlagsMapTexture = nullptr;
	
	UnlockAllCountriesFlagColors();
	
	CountriesFlagColors.Empty();
	CountriesFlagColorsCount.Empty();
}

void UFlagsMap::Init(UScenario* Scenario)
{
	FlagsMapTexture = Scenario->FlagsMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(FlagsMapTexture);
	UpdateAllBoxes();
	FlagsMapTexture->UpdateResource();
}

void UFlagsMap::UpdateBoxes(const TArray<TSharedPtr<FProvincesBox>>& Boxes)
{
	TArray<FRunnableThread*> Threads;
	
	FColor* FlagsColors = FTextureUtils::GetPixels(FlagsMapTexture, LOCK_READ_WRITE);

	for (const auto& Box: Boxes)
	{
		const FColor* CountryFlagColors = GetCountryFlagColors(Box->GetCountry());
		FVector2d CountryFlagColorsSizeVector = FTextureUtils::GetTextureSizeVector(Box->GetCountry()->GetFlag());
		Threads.Add(UpdateBox(Box, FlagsColors, CountryFlagColors, CountryFlagColorsSizeVector));
	}
	
	for (const auto& Thread: Threads)
	{
		Thread->WaitForCompletion();
	}

	UnlockAllCountriesFlagColors();
	FTextureUtils::UnlockPixels(FlagsMapTexture);

	IsUpdated = true;
}

void UFlagsMap::BoxWasUpdated(const TSharedPtr<FProvincesBox>& Box)
{
	FColor* FlagsColors = FTextureUtils::GetPixels(FlagsMapTexture, LOCK_READ_WRITE);

	const FColor* CountryFlagColors = GetCountryFlagColors(Box->GetCountry());
	FVector2d CountryFlagColorsSizeVector = FTextureUtils::GetTextureSizeVector(Box->GetCountry()->GetFlag());
	
	UpdateBox(Box, FlagsColors, CountryFlagColors, CountryFlagColorsSizeVector)->WaitForCompletion();
	
	UnlockAllCountriesFlagColors();
	FTextureUtils::UnlockPixels(FlagsMapTexture);

	IsUpdated = true;
}