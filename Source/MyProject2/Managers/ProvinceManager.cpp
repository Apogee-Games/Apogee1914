#include "ProvinceManager.h"

#include "MyProject2/TextureUtils.h"

UProvinceManager::UProvinceManager()
{
	
	const ConstructorHelpers::FObjectFinder<UDataTable> ProvincesDescriptionFinder(TEXT("/Game/Sources/provinces_description"));
	if (ProvincesDescriptionFinder.Succeeded())
	{
		ProvinceDescriptionDataTable = ProvincesDescriptionFinder.Object;
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

	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");

	SelectionMapTexture = FTextureUtils::LoadTexture("/Game/maps/province");

	CountriesMapTexture = FTextureUtils::LoadTexture("/Game/maps/country");

	OutlinesMapTexture = FTextureUtils::LoadTexture("/Game/maps/outlines");

}

FProvinceDescription* UProvinceManager::GetProvince(const FColor& ProvinceColor) const
{
	if (ProvinceColor == FColor(0, 0, 0) || ProvinceColor == FColor(255, 255, 255)) return nullptr;
	return reinterpret_cast<FProvinceDescription*>(ProvinceDescriptionDataTable->FindRowUnchecked(FName(ProvinceColor.ToHex())));

}

FColor UProvinceManager::GetCountryColor(const FColor& ProvinceColor) const
{
	if (ProvinceColor == FColor(0, 0, 0) || ProvinceColor == FColor(255, 255, 255)) return FColor(20, 20, 20);
	const FProvinceDescription* Province = reinterpret_cast<FProvinceDescription*>(ProvinceDescriptionDataTable->FindRowUnchecked(FName(ProvinceColor.ToHex())));
	if (!Province) return FColor(20, 20, 20);

	const FCountry* Country = reinterpret_cast<FCountry*>(CountryDescriptionDataTable->FindRowUnchecked(FName(Province->CountryTag)));
	return Country ? Country->GetColor() : FColor(20, 20, 20);
}

FState* UProvinceManager::GetState(const FString& StateId) const
{
	return reinterpret_cast<FState*>(StateDescriptionDataTable->FindRowUnchecked(FName(StateId)));
}

bool UProvinceManager::AreProvincesInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const
{
	const FProvinceDescription* ProvinceA = GetProvince(ProvinceAColor);
	const FProvinceDescription* ProvinceB = GetProvince(ProvinceBColor);
	return ProvinceA && ProvinceB && ProvinceA->StateId == ProvinceB->StateId;
}

bool UProvinceManager::AreProvincesNotInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const
{
	
	const FProvinceDescription* ProvinceA = GetProvince(ProvinceAColor);
	const FProvinceDescription* ProvinceB = GetProvince(ProvinceBColor);
	return ProvinceA && ProvinceB && ProvinceA->StateId != ProvinceB->StateId;
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


