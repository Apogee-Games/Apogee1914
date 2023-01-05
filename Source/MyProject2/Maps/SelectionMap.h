#pragma once
#include "MyProject2/MyGameState.h"

class FSelectionMap
{
public:
	FSelectionMap();

	explicit FSelectionMap(AMyGameState* GameState);
	
	FSelectionMap(UTexture2D* SelectionMapTexture, UTexture2D* ProvincesMapTexture, AMyGameState* GameState);

	void SelectProvince(const FColor& Color);

	void SelectProvince(const FVector2d& Point);
	
	FColor GetProvinceColor(const FVector2d& Point) const;

	
private:
	AMyGameState* GameState;

	UTexture2D* SelectionMapTexture;

	UTexture2D* ProvincesMapTexture;
	
	FVector2D SizeVector;
	
	const FColor SelectedProvinceColor = FColor(75, 75, 150);

	const FColor NonSelectedProvinceColor = FColor(0, 0, 0);

	FColor SelectedProvince = FColor(0, 0, 0);
	
	
};
