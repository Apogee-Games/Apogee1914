#pragma once
#include "Administration/Interfaces/Observer/ProvinceControllingCountryObserver.h"
#include "Administration/Managers/CountriesManager.h"
#include "Maps/Interfaces/Observer/CountryDistancesObserver.h"
#include "CountriesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UCountriesMap: public UBaseManager, public IProvinceControllingCountryObserver, public ICountryDistancesObserver
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void Tick();

	virtual void SetScenario(UScenario* Scenario) override;
	
	void UpdateCountriesMapColors(const TArray<UProvince*>& Provinces);

	void UpdateAllCountriesMapColors();
	
	virtual void ProvinceHasNewControllingCountry(UProvince* Province) override;
	
	virtual void CountryDistancesWereUpdated(const TArray<UProvince*>& Provinces) override;

	virtual ELoadStage GetLoadStage() override;
	
	UPROPERTY(EditDefaultsOnly)
	int32 CrossLineWidth = 10;
private:
	bool IsUpdated = true;
	
	UPROPERTY()	
	UTexture2D* CountriesMapTexture;

	FVector2D SizeVector;

	FRunnableThread* UpdateCountryColor(UProvince* Province, FColor* CountriesColor) const;

	void Clear();

	void Init(UScenario* Scenario);
};