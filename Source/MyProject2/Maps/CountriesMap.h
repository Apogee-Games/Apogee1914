#pragma once
#include "MyProject2/MyGameState.h"

class FCountriesMap
{
public:
	FCountriesMap();

	explicit FCountriesMap(AMyGameState* GameState);

	
	FCountriesMap(UTexture2D* CountriesMapTexture, UTexture2D* ProvincesMapTexture, AMyGameState* GameState);

	void UpdateCountriesMapColors() const;

private:
	AMyGameState* GameState;
	
	UTexture2D* CountriesMapTexture;

	UTexture2D* ProvincesMapTexture;

	FVector2D SizeVector;

	TArray<int> FindProvincesBorders(const FColor* ProvincesColor, const int Width, const int Height) const;

	int* FindDistancesFromBorders(const TArray<int>& Borders, const int Width, const int Height) const;
};
