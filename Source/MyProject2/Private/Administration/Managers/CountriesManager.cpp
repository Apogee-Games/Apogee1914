
#include "Administration/Managers/CountriesManager.h"

#include "MyGameInstance.h"
#include "Administration/Managers/ProvinceManager.h"

void UCountriesManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

const TArray<UCountryDescription*>& UCountriesManager::GetCountriesDescriptions()
{
	return CountriesDescriptions;
}

bool UCountriesManager::ExistsCountryWithSuchProvince(const FColor& ProvinceColor) const
{
	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	const UProvince* Province = ProvinceManager->GetProvince(ProvinceColor);
	return ExistsCountryWithSuchProvince(Province);
}

bool UCountriesManager::ExistsCountryWithSuchProvince(const UProvince* Province) const
{
	return Province && Province->GetOwnerCountry() && CountryMap.Contains(Province->GetOwnerCountry()->GetId());
}

bool UCountriesManager::AreProvincesOwnedBySameCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const
{
	if (ProvinceAColor == ProvinceBColor) return true;
	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	const UProvince* ProvinceA = ProvinceManager->GetProvince(ProvinceAColor);
	const UProvince* ProvinceB = ProvinceManager->GetProvince(ProvinceBColor);
	return AreProvincesOwnedBySameCountry(ProvinceA, ProvinceB);
}

bool UCountriesManager::AreProvincesOwnedBySameCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const 
{
	return ProvinceA && ProvinceB && ProvinceA->GetOwnerCountry() == ProvinceB->GetOwnerCountry();
}

bool UCountriesManager::AreProvincesControlledBySameCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const
{
	if (ProvinceAColor == ProvinceBColor) return true;
	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	const UProvince* ProvinceA = ProvinceManager->GetProvince(ProvinceAColor);
	const UProvince* ProvinceB = ProvinceManager->GetProvince(ProvinceBColor);
	return AreProvincesControlledBySameCountry(ProvinceA, ProvinceB);
}

bool UCountriesManager::AreProvincesControlledBySameCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const 
{
	return ProvinceA && ProvinceB && ProvinceA->GetCountryController() == ProvinceB->GetCountryController();
}

bool UCountriesManager::AreProvincesOwnedByDifferentCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const
{
	return !AreProvincesOwnedBySameCountry(ProvinceAColor, ProvinceBColor);
}

bool UCountriesManager::AreProvincesOwnedByDifferentCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const
{
	return !AreProvincesOwnedBySameCountry(ProvinceA, ProvinceB);
}

bool UCountriesManager::AreProvincesControlledByDifferentCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const
{
	return !AreProvincesControlledBySameCountry(ProvinceAColor, ProvinceBColor);
}

bool UCountriesManager::AreProvincesControlledByDifferentCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const
{
	return !AreProvincesControlledBySameCountry(ProvinceA, ProvinceB);
}

UCountry* UCountriesManager::GetCountry(UCountryDescription* CountryDescription)
{
	return CountryMap.Contains(CountryDescription) ? CountryMap[CountryDescription] : nullptr;
}

const TMap<UCountryDescription*, UCountry*>& UCountriesManager::GetCountryMap() const
{
	return CountryMap;
}

void UCountriesManager::Clear()
{
	for (const auto& [Name, Country]: CountryMap)
	{
		Country->MarkAsGarbage();
	}
	CountryMap.Empty();
	CountriesDescriptions.Empty();
}

void UCountriesManager::Init(UScenario* Scenario)
{
	CountriesDescriptions = Scenario->CountriesDescriptions;
	for (const auto& Description: Scenario->CountriesDescriptions)
	{
		UCountry* Country = NewObject<UCountry>(this);
		Country->Init(Description); // TODO: Add removal of countries
		CountryMap.Add(Description, Country);
	}
}
