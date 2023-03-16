
#include "Administration/Managers/CountriesManager.h"

#include "MyGameInstance.h"
#include "Administration/Managers/ProvinceManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"


bool UCountriesManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UCountriesManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	const UScenario* Scenario = GetWorld()->GetGameInstance<UMyGameInstance>()->ActiveScenario;
	InitCountries(Scenario->CountryDescriptionDataTable);
	for (const auto& Pair: Scenario->CountryDescriptionDataTable->GetRowMap())
	{
		CountriesTagsList.Add(Pair.Key);
	}
}

const TArray<FName>& UCountriesManager::GetCountriesTagsList()
{
	return CountriesTagsList;
}

bool UCountriesManager::ExistsCountryWithSuchProvince(const FColor& ProvinceColor) const
{
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
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
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
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
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
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

const TMap<FName, UCountry*> UCountriesManager::GetCountryMap() const
{
	return CountryMap;
}

void UCountriesManager::InitCountries(UDataTable* CountryDescriptionDataTable)
{
	for (const auto& [Key, Value]: CountryDescriptionDataTable->GetRowMap())
	{
		UCountry* Country = NewObject<UCountry>(GetWorld());
		Country->Init(reinterpret_cast<FCountryDescription*>(Value));
		CountryMap.Add(Key, Country);
	}
}
