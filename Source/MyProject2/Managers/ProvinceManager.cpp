#include "ProvinceManager.h"

#include "MyProject2/TextureUtils.h"

UProvinceManager::UProvinceManager()
{
	
	const ConstructorHelpers::FObjectFinder<UDataTable> ProvincesDescriptionFinder(TEXT("/Game/Sources/provinces_description"));
	if (ProvincesDescriptionFinder.Succeeded())
	{
		ProvinceDescriptionDataTable = ProvincesDescriptionFinder.Object;
		InitProvinces();
	}

	const ConstructorHelpers::FObjectFinder<UDataTable> CountriesDescriptionFinder(TEXT("/Game/Sources/countries_description"));
	if (CountriesDescriptionFinder.Succeeded())
	{
		CountryDescriptionDataTable = CountriesDescriptionFinder.Object;
	}
		
	const ConstructorHelpers::FObjectFinder<UDataTable> StateDescriptionFinder(TEXT("/Game/Sources/states_description"));
	if (StateDescriptionFinder.Succeeded())
	{
		StateDescriptionDataTable = StateDescriptionFinder.Object;
	}

	const ConstructorHelpers::FObjectFinder<UDataTable> TerrainDescriptionFinder(TEXT("/Game/Sources/terrain_description"));
	if (TerrainDescriptionFinder.Succeeded())
	{
		TerrainDescriptionDataTable = TerrainDescriptionFinder.Object;
	}

	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");

	SelectionMapTexture = FTextureUtils::LoadTexture("/Game/maps/province");

	CountriesMapTexture = FTextureUtils::LoadTexture("/Game/maps/country");

	OutlinesMapTexture = FTextureUtils::LoadTexture("/Game/maps/outlines");

	
}

UProvince* UProvinceManager::GetProvince(const FColor& ProvinceColor) const
{
	return GetProvince(ProvinceColor.ToHex());
}

UProvince* UProvinceManager::GetProvince(const FString& ProvinceColorHex) const
{
	return ProvinceMap.FindRef(FName(ProvinceColorHex));
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

UTexture2D* UProvinceManager::GetProvincesMapTexture() const
{
	return ProvincesMapTexture;
}

UTexture2D* UProvinceManager::GetSelectionMapTexture() const
{
	return SelectionMapTexture;

}

UTexture2D* UProvinceManager::GetCountriesMapTexture() const
{
	return CountriesMapTexture;

}

UTexture2D* UProvinceManager::GetOutlinesMapTexture() const
{
	return OutlinesMapTexture;
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


