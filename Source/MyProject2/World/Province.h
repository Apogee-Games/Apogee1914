#pragma once

class FProvince
{
public:
	FProvince()
	{
	}

	FProvince(const FColor& Color, const FString& Name, const FColor& CountryColor, const int& Population) : Color(Color), Name(Name),
		CountryColor(CountryColor), Population(Population)
	{
	}

	FColor GetColor() const;

	FColor GetCountryColor() const;

	FString GetName() const;

private:
	FColor Color;
	FString Name;
	FColor CountryColor;
	int Population;
};
