#include "Province.h"

#include <string>


FProvince::FProvince()
{
}

FProvince::FProvince(const FColor& Color, const FString& Name, const FString& CountryTag, const int& Population):
	Color(Color), Name(Name),
	CountryTag(CountryTag), Population(Population)
{
}

FColor FProvince::GetColor() const
{
	return Color;
}

FString FProvince::GetCountryTag() const
{
	return CountryTag;
}

FString FProvince::GetName() const
{
	return Name;
}

int FProvince::GetPopulation() const
{
	return Population;
}
