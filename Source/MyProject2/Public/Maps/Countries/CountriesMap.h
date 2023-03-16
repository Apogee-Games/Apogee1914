#pragma once
#include "Administration/Interfaces/Observer/ProvinceControllingCountryObserver.h"
#include "Administration/Managers/CountriesManager.h"
#include "Maps/Interfaces/Observer/CountryDistancesObserver.h"
#include "CountriesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UCountriesMap: public UWorldSubsystem, public IProvinceControllingCountryObserver, public ICountryDistancesObserver
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

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
