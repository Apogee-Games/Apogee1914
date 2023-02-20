#include "CountriesMap.h"

#include "CountryMapUpdater.h"
#include "MyProject2/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Maps/Precalculations/ProvincesMap.h"
#include "MyProject2/Utils/TextureUtils.h"

void UCountriesMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CountriesMapTexture = FTextureUtils::LoadTexture("/Game/maps/country");
	SizeVector = FTextureUtils::GetTextureSizeVector(CountriesMapTexture);
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

void UCountriesMap::UpdateAllCountriesMapColors() const
{
	UpdateCountriesMapColors(GetWorld()->GetSubsystem<UProvinceManager>()->GetAllProvinces());
}

FRunnableThread* UCountriesMap::UpdateCountryColor(UProvince* Province, FColor* CountriesColor) const
{
	const UProvincesMap* ProvincesMap = GetWorld()->GetSubsystem<UProvincesMap>();
	const TArray<int32>& PixelsToUpdate = ProvincesMap->GetProvincePositions(Province->GetId());
	const int* Distances = ProvincesMap->GetCountriesDistances();
	FCountryMapUpdater* Updater = new FCountryMapUpdater(CountriesColor, PixelsToUpdate, Province, Distances, SizeVector, CrossLineWidth);
	return FRunnableThread::Create(Updater, *Province->GetName());	
}
