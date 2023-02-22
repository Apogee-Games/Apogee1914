#pragma once
#include "Engine/DataTable.h"
#include "MyProject2/Administration/Instances/Country.h"
#include "MyProject2/Administration/Instances/Province.h"

#include "CountriesManager.generated.h"

UCLASS()
class UCountriesManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	const TArray<FString>& GetCountriesTagsList();
	
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

	UCountry* GetCountry(const FString& Tag);
private:
	UPROPERTY()
	TMap<FString, UCountry*> CountryMap;
	
	TArray<FString> CountriesTagsList;

	void InitCountries(UDataTable* CountryDescriptionDataTable);
};
