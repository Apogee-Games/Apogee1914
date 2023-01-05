#pragma once
#include "MyProject2/MyGameState.h"

class FObjectMap
{
public:
	FObjectMap();

	explicit FObjectMap(AMyGameState* GameState);
	
	FObjectMap(UTexture2D* ProvincesMapTexture, AMyGameState* GameState);

	TMap<FColor, int> CalculateProvincesCenters() const;

private:
	AMyGameState* GameState;
	
	UTexture2D* ProvincesMapTexture;

	FVector2D SizeVector;
};
