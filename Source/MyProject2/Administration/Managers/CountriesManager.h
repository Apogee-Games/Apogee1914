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
	
	const FColor* GetCountryColor(const FColor& ProvinceColor);
	
	const FColor* GetCountryColor(const UProvince* Province);

	TArray<FString>* GetCountriesTagsList();
	
	bool ExistsCountryWithSuchProvince(const FColor& ProvinceColor) const;

	bool ExistsCountryWithSuchProvince(const UProvince* Province) const;
	
	bool AreProvincesInSameCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesInSameCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const;

private:
	UPROPERTY()
	TMap<FString, UCountry*> CountryMap;
	
	TArray<FString> CountriesTagsList;

	void InitCountries(UDataTable* CountryDescriptionDataTable);
	
};
