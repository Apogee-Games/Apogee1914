#include "FlagsMap.h"

#include "FlagBoxUpdater.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Maps/Precalculations/ProvincesMap.h"
#include "MyProject2/Utils/TextureUtils.h"

void UFlagsMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FlagsMapTexture = FTextureUtils::LoadTexture("/Game/maps/flags");
	SizeVector = FTextureUtils::GetTextureSizeVector(FlagsMapTexture);
}

void UFlagsMap::UpdateAllBoxes()
{
	UpdateBoxes(GetWorld()->GetSubsystem<UBoxesMap>()->GetBoxes());
}

FRunnableThread* UFlagsMap::UpdateBox(const TSharedPtr<FProvincesBox>& Box, FColor* FlagsColors, const FColor* CountryFlagColor, const FVector2d& CountryFlagColorSizeVector)
{
	const UProvincesMap* ProvincesMap = GetWorld()->GetSubsystem<UProvincesMap>();
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
	FlagsMapTexture->UpdateResource();

}

void UFlagsMap::BoxWasUpdated(const TSharedPtr<FProvincesBox>& Box)
{
	FColor* FlagsColors = FTextureUtils::GetPixels(FlagsMapTexture, LOCK_READ_WRITE);

	const FColor* CountryFlagColors = GetCountryFlagColors(Box->GetCountry());
	FVector2d CountryFlagColorsSizeVector = FTextureUtils::GetTextureSizeVector(Box->GetCountry()->GetFlag());
	
	UpdateBox(Box, FlagsColors, CountryFlagColors, CountryFlagColorsSizeVector)->WaitForCompletion();
	
	UnlockAllCountriesFlagColors();
	FTextureUtils::UnlockPixels(FlagsMapTexture);
	FlagsMapTexture->UpdateResource();
}

void UFlagsMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UBoxesMap>()->RegisterOnFullInitializationAction(this, &UFlagsMap::UpdateAllBoxes);
	GetWorld()->GetSubsystem<UBoxesMap>()->AddBoxObserver(this);
}
