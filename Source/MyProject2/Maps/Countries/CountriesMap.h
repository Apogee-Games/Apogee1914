#pragma once
#include "MyProject2/MyGameState.h"
#include "MyProject2/Administration/Interfaces/Observer/ProvinceControllingCountryObserver.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Maps/Interfaces/Observer/CountryDistancesObserver.h"
#include "CountriesMap.generated.h"

UCLASS()
class UCountriesMap: public UWorldSubsystem, public IProvinceControllingCountryObserver, public ICountryDistancesObserver
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void UpdateCountriesMapColors(const TArray<UProvince*>& Provinces) const;

	void UpdateAllCountriesMapColors();
	
	virtual void ProvinceHasNewControllingCountry(UProvince* Province) override;
	
	virtual void CountryDistancesWereUpdated(const TArray<UProvince*>& Provinces) override;
private:
	int32 CrossLineWidth = 10;
	
	UPROPERTY()	
	UTexture2D* CountriesMapTexture;

	FVector2D SizeVector;

	FRunnableThread* UpdateCountryColor(UProvince* Province, FColor* CountriesColor) const;
};
