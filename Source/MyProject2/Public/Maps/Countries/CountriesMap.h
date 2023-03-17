#pragma once
#include "Administration/Interfaces/Observer/ProvinceControllingCountryObserver.h"
#include "Administration/Managers/CountriesManager.h"
#include "Maps/Interfaces/Observer/CountryDistancesObserver.h"
#include "CountriesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UCountriesMap: public UGameInstanceSubsystem, public IProvinceControllingCountryObserver, public ICountryDistancesObserver
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SetScenario(UScenario* Scenario);
	
	void UpdateCountriesMapColors(const TArray<UProvince*>& Provinces) const;

	void UpdateAllCountriesMapColors();
	
	virtual void ProvinceHasNewControllingCountry(UProvince* Province) override;
	
	virtual void CountryDistancesWereUpdated(const TArray<UProvince*>& Provinces) override;

	UPROPERTY(EditDefaultsOnly)
	int32 CrossLineWidth = 10;
private:
	UPROPERTY()	
	UTexture2D* CountriesMapTexture;

	FVector2D SizeVector;

	FRunnableThread* UpdateCountryColor(UProvince* Province, FColor* CountriesColor) const;
};