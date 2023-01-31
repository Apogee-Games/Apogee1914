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

const FColor* UCountriesManager::GetOwnerCountryColor(const FColor& ProvinceColor)
{
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	const UProvince* Province = ProvinceManager->GetProvince(ProvinceColor);
	return GetOwnerCountryColor(Province);
}

const FColor* UCountriesManager::GetOwnerCountryColor(const UProvince* Province)
{
	if (!Province || !CountryMap.Contains(Province->GetOwnerCountryTag())) return nullptr;
	UCountry* Country = CountryMap[Province->GetOwnerCountryTag()];
	return Country ? Country->GetColor(): nullptr;
}

const FColor* UCountriesManager::GetControllerCountryColor(const FColor& ProvinceColor)
{
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	const UProvince* Province = ProvinceManager->GetProvince(ProvinceColor);
	return GetControllerCountryColor(Province);
}

const FColor* UCountriesManager::GetControllerCountryColor(const UProvince* Province)
{
	if (!Province || !CountryMap.Contains(Province->GetControllerCountryTag())) return nullptr;
	UCountry* Country = CountryMap[Province->GetControllerCountryTag()];
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
	return Province && CountryMap.Contains(Province->GetOwnerCountryTag());
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
	return ProvinceA && ProvinceB && ProvinceA->GetOwnerCountryTag() == ProvinceB->GetOwnerCountryTag();
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
	return ProvinceA && ProvinceB && ProvinceA->GetControllerCountryTag() == ProvinceB->GetControllerCountryTag();
}

UCountry* UCountriesManager::GetCountry(const FString& Tag)
{
	return CountryMap.Contains(Tag) ? CountryMap[Tag] : nullptr;
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
