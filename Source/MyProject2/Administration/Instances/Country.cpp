#include "Country.h"

#include "MyProject2/Utils/TextureUtils.h"

void UCountry::Init(FCountryDescription* CountryDescription)
{
	Name = CountryDescription->CountryName;
	Tag = CountryDescription->Tag;
	Color = CountryDescription->Color;
	Flag = FTextureUtils::LoadTexture("/Game/images/flags/" + Tag);
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

UTexture2D* UCountry::GetFlag()
{
	return Flag;
}
