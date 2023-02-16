#include "CountriesManager.h"

#include "ProvinceManager.h"

void UCountriesManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UDataTable* CountryDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/countries_description"));
	InitCountries(CountryDescriptionDataTable);
	
	for (const auto& Pair: CountryDescriptionDataTable->GetRowMap())
	{
		CountriesTagsList.Add(Pair.Key.ToString());
	}
}

const TArray<FString>& UCountriesManager::GetCountriesTagsList()
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
	return ProvinceA && ProvinceB && ProvinceA->GetControllerCountry() == ProvinceB->GetControllerCountry();
}

UCountry* UCountriesManager::GetCountry(const FString& Tag)
{
	return CountryMap.Contains(Tag) ? CountryMap[Tag] : nullptr;
}

void UCountriesManager::InitCountries(UDataTable* CountryDescriptionDataTable)
{
	for (const auto& [Key, Value]: CountryDescriptionDataTable->GetRowMap())
	{
		UCountry* Country = NewObject<UCountry>(GetWorld());
		Country->Init(reinterpret_cast<FCountryDescription*>(Value));
		CountryMap.Add(Key.ToString(), Country);
	}
}
