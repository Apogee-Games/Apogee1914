#include "Province.h"


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
