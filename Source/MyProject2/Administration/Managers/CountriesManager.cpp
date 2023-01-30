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

const FColor* UCountriesManager::GetCountryColor(const FColor& ProvinceColor)
{
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	const UProvince* Province = ProvinceManager->GetProvince(ProvinceColor);
	return GetCountryColor(Province);
}

const FColor* UCountriesManager::GetCountryColor(const UProvince* Province)
{
	if (!Province || !CountryMap.Contains(Province->GetCountryTag())) return nullptr;
	UCountry* Country = CountryMap[Province->GetCountryTag()];
	return Country ? Country->GetColor(): nullptr;
}

TArray<FString>* UCountriesManager::GetCountriesTagsList()
{
	return &CountriesTagsList;
}

bool UCountriesManager::ExistsCountryWithSuchProvince(const FColor& ProvinceColor) const
{
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	const UProvince* Province = ProvinceManager->GetProvince(ProvinceColor);
	return ExistsCountryWithSuchProvince(Province);
}

bool UCountriesManager::ExistsCountryWithSuchProvince(const UProvince* Province) const
{
	return Province && CountryMap.Contains(Province->GetCountryTag());
}

bool UCountriesManager::AreProvincesInSameCountry(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const
{
	if (ProvinceAColor == ProvinceBColor) return true;
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	const UProvince* ProvinceA = ProvinceManager->GetProvince(ProvinceAColor);
	const UProvince* ProvinceB = ProvinceManager->GetProvince(ProvinceBColor);
	return AreProvincesInSameCountry(ProvinceA, ProvinceB);
}

bool UCountriesManager::AreProvincesInSameCountry(const UProvince* ProvinceA, const UProvince* ProvinceB) const 
{
	return ProvinceA && ProvinceB && ProvinceA->GetCountryTag() == ProvinceB->GetCountryTag();
}

void UCountriesManager::InitCountries(UDataTable* CountryDescriptionDataTable)
{
	for (const auto& [Key, Value]: CountryDescriptionDataTable->GetRowMap())
	{
		UCountry* Country = NewObject<UCountry>();
		Country->Init(reinterpret_cast<FCountryDescription*>(Value));
		CountryMap.Add(Key.ToString(), Country);
	}
}
