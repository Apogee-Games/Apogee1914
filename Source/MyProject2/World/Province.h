#pragma once

class FProvince
{
public:
	FProvince()
	{
	}

	FProvince(const FColor& Color, const FString& Name, const FColor& CountryColor) : Color(Color), Name(Name),
		CountryColor(CountryColor)
	{
	}

	FColor GetColor() const;

	FColor GetCountryColor() const;

	FString GetName() const;

private:
	FColor Color;
	FString Name;
	FColor CountryColor;
};
