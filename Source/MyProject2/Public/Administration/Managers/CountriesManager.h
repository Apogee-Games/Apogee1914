#pragma once
#include "Engine/DataTable.h"
#include "Administration/Instances/Country.h"
#include "Administration/Instances/Province.h"

#include "CountriesManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UCountriesManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	const TArray<FName>& GetCountriesTagsList();
	
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

	UCountry* GetCountry(const FName& Tag);

	const TMap<FName, UCountry*> GetCountryMap() const;
private:
	UPROPERTY()
	TMap<FName, UCountry*> CountryMap;
	
	TArray<FName> CountriesTagsList;

	void InitCountries(UDataTable* CountryDescriptionDataTable);
};
