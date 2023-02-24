#include "Country.h"

#include "MyProject2/Utils/TextureUtils.h"

void UCountry::Init(FCountryDescription* CountryDescription)
{
	Name = CountryDescription->CountryName;
	Tag = CountryDescription->Tag;
	Color = CountryDescription->Color;

	Flag = FTextureUtils::LoadTexture("/Game/images/flags/" + Tag.ToString());

	InitStrata();

	Storage = NewObject<UStorage>();
	Market = NewObject<UMarket>();
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

UStorage* UCountry::GetStorage() const
{
	return Storage;
}

TArray<UStorage*> UCountry::GetStorages() const
{
	return {Storage, LowerStrata->GetStorage(), MiddleStrata->GetStorage(), UpperStrata->GetStorage()};
}

void UCountry::InitStrata()
{
	LowerStrata = NewObject<UStrata>();
	LowerStrata->Init("LOW");
	MiddleStrata = NewObject<UStrata>();
	MiddleStrata->Init("MIDDLE");
	UpperStrata = NewObject<UStrata>();
	UpperStrata->Init("UPPER");
	// TODO: Add proper initialization 
}
