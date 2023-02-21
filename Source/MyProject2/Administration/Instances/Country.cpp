#include "Country.h"

#include "MyProject2/Utils/TextureUtils.h"

void UCountry::Init(FCountryDescription* CountryDescription)
{
	Name = CountryDescription->CountryName;
	Tag = CountryDescription->Tag;
	Color = CountryDescription->Color;
	Flag = FTextureUtils::LoadTexture("/Game/images/flags/" + Tag.ToString());
}

const FColor& UCountry::GetColor() const
{
	return Color;
}

const FName& UCountry::GetName() const
{
	return Name;
}

const FName& UCountry::GetTag() const
{
	return Tag;
}

UTexture2D* UCountry::GetFlag() const
{
	return Flag;
}
