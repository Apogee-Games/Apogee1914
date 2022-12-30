#pragma once

class FProvince
{
public:
	FProvince()
	{
	}

	FProvince(const FColor& Color, const FString& Name, const FString& CountryTag, const int& Population) : Color(Color), Name(Name),
		CountryTag(CountryTag), Population(Population)
	{
	}

	FColor GetColor() const;

	FString GetCountryTag() const;

	FString GetName() const;

private:
	FColor Color;
	FString Name;
	FString CountryTag;
	int Population;
};
