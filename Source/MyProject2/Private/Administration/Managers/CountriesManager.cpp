
#include "Administration/Managers/CountriesManager.h"

#include "MyGameInstance.h"
#include "Administration/Managers/ProvinceManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

void UCountriesManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

const TArray<FName>& UCountriesManager::GetCountriesTagsList()
{
	return CountriesTagsList;
}

bool UCountriesManager::ExistsCountryWithSuchProvince(const FColor& ProvinceColor) const
{
	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	const UProvince* Province = ProvinceManager->GetProvince(ProvinceColor);
	return ExistsCountryWithSuchProvince(Province);
}

bool UCountriesManager::ExistsCountryWithSuchProvince(const UProvince* Province) const
{
	return Province && Province->GetOwnerCountry() && CountryMap.Contains(Province->GetOwnerCountry()->GetTag());
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

UCountry* UCountriesManager::GetCountry(const FName& Tag)
{
	return CountryMap.Contains(Tag) ? CountryMap[Tag] : nullptr;
}

const TMap<FName, UCountry*>& UCountriesManager::GetCountryMap() const
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
	CountriesTagsList.Empty();
}

void UCountriesManager::Init(UScenario* Scenario)
{
	for (const auto& [Key, Value]: Scenario->CountryDescriptionDataTable->GetRowMap())
	{
		UCountry* Country = NewObject<UCountry>(this);
		Country->Init(reinterpret_cast<FCountryDescription*>(Value)); // TODO: Add removal of countries
		CountryMap.Add(Key, Country);
	}

	for (const auto& Pair: Scenario->CountryDescriptionDataTable->GetRowMap())
	{
		CountriesTagsList.Add(Pair.Key);
	}
}
