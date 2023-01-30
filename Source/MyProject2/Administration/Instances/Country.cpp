#include "Country.h"

void UCountry::Init(FCountryDescription* CountryDescription)
{
	Name = CountryDescription->CountryName;
	Tag = CountryDescription->Tag;
	Color = CountryDescription->Color;
}

const FColor* UCountry::GetColor()
{
	return &Color;
}

const FString& UCountry::GetName()
{
	return Name;
}

const FString& UCountry::GetTag() const
{
	return Tag;
}
