#include "ProvinceManager.h"

void UProvinceManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CountryDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/countries_description"));

	for (const auto& Pair: CountryDescriptionDataTable->GetRowMap())
	{
		CountriesTagsList.Add(Pair.Key.ToString());
	}

	StateDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/states_description"));

	TerrainDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/terrain_description"));
	
	ProvinceDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/provinces_description"));

	InitProvinces();
}

UProvince* UProvinceManager::GetProvince(const FColor& ProvinceColor) const
{
	return GetProvince(ProvinceColor.ToHex());
}

UProvince* UProvinceManager::GetProvince(const FString& ProvinceColorHex) const
{
	return ProvinceMap.Contains(FName(ProvinceColorHex)) ? ProvinceMap[FName(ProvinceColorHex)] : nullptr;
}

FColor UProvinceManager::GetCountryColor(const FColor& ProvinceColor) const
{
	if (ProvinceColor == FColor(0, 0, 0) || ProvinceColor == FColor(255, 255, 255)) return FColor(20, 20, 20);

	UProvince* Province = GetProvince(ProvinceColor);
	if (!Province) return FColor(20, 20, 20);

	const FCountry* Country = reinterpret_cast<FCountry*>(CountryDescriptionDataTable->FindRowUnchecked(FName(Province->GetCountryTag())));
	return Country ? Country->GetColor() : FColor(20, 20, 20);
}

FState* UProvinceManager::GetState(const FString& StateId) const
{
	return reinterpret_cast<FState*>(StateDescriptionDataTable->FindRowUnchecked(FName(StateId)));
}

bool UProvinceManager::AreProvincesInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const
{
	const UProvince* ProvinceA = GetProvince(ProvinceAColor);
	const UProvince* ProvinceB = GetProvince(ProvinceBColor);
	return ProvinceA && ProvinceB && ProvinceA->GetStateId() == ProvinceB->GetStateId();
}

bool UProvinceManager::AreProvincesNotInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const
{
	
	return !AreProvincesInTheSameState(ProvinceAColor, ProvinceBColor);
}

void UProvinceManager::InitProvinces()
{
	for(const auto& [Key,Value]: ProvinceDescriptionDataTable->GetRowMap()) {
		if(Value == nullptr) continue;
		// GetProvinceData
		FProvinceDescription* ProvinceDescription = reinterpret_cast<FProvinceDescription*>(Value);
		UProvince* Province = NewObject<UProvince>(); // Get New Province
		Province->Init(ProvinceDescription, TerrainDescriptionDataTable, nullptr); // Init Province Data
		ProvinceMap.Add(Key, Province); // Save Province Data to ProvinceMap<Name, UProvince*>
	}
}

TArray<FString>* UProvinceManager::GetCountriesTagsList()
{
	return &CountriesTagsList;
}

bool UProvinceManager::ExistsCountryWithSuchProvince(const FColor& ProvinceColor) const
{
	if (ProvinceColor == FColor(0, 0, 0) || ProvinceColor == FColor(255, 255, 255)) return false;

	UProvince* Province = GetProvince(ProvinceColor);
	if (!Province) return false;

	const FCountry* Country = reinterpret_cast<FCountry*>(CountryDescriptionDataTable->FindRowUnchecked(FName(Province->GetCountryTag())));
	return Country != nullptr;
}


