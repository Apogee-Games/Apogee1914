#pragma once
#include "Scenario.h"
#include "Administration/Instances/Country.h"
#include "Administration/Instances/Province.h"

#include "CountriesManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UCountriesManager: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	const TArray<UCountryDescription*>& GetCountriesDescriptions();
	
	bool ExistsCountryWithSuchProvince(const FColor& ProvinceColor) const;

	bool ExistsCountryWithSuchProvince(const UProvince* Province) const;
	
	bool AreProvincesOwnedBySameCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesOwnedBySameCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const;

	bool AreProvincesControlledBySameCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesControlledBySameCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const;

	bool AreProvincesOwnedByDifferentCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesOwnedByDifferentCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const;

	bool AreProvincesControlledByDifferentCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesControlledByDifferentCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const;

	UCountry* GetCountry(UCountryDescription* CountryDescription);

	const TMap<UCountryDescription*, UCountry*>& GetCountryMap() const;
private:
	UPROPERTY()
	TMap<UCountryDescription*, UCountry*> CountryMap;

	UPROPERTY()
	TArray<UCountryDescription*> CountriesDescriptions;

	void Clear();

	void Init(UScenario* Scenario);
};
