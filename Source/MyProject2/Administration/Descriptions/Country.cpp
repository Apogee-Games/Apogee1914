#include "Country.h"

FCountry::FCountry()
{
}

FCountry::FCountry(const FString& Tag, const FColor& Color): Tag(Tag), Color(Color)
{	
}

FString FCountry::GetTag() const
{
	return Tag;
}

FColor FCountry::GetColor() const
{
	return Color;
}
