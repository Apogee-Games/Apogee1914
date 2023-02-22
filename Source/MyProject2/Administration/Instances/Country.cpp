#include "Country.h"

#include "MyProject2/Utils/TextureUtils.h"

void UCountry::Init(FCountryDescription* CountryDescription)
{
	Name = CountryDescription->CountryName;
	Tag = CountryDescription->Tag;
	Color = CountryDescription->Color;
	Flag = FTextureUtils::LoadTexture("/Game/images/flags/" + Tag);
	// Strata Initialization
	LowerStrata = NewObject<UStrata>();
	MiddleStrata = NewObject<UStrata>();
	UpperStrata = NewObject<UStrata>();
	// Market Initialization
	Market = NewObject<UMarket>();
	
}

const FColor& UCountry::GetColor() const
{
	return Color;
}

const FString& UCountry::GetName() const
{
	return Name;
}

const FString& UCountry::GetTag() const
{
	return Tag;
}

UTexture2D* UCountry::GetFlag() const
{
	return Flag;
}
