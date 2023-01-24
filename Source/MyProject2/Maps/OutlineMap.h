#pragma once
#include "MyProject2/MyGameState.h"

class FOutlineMap
{
public:
	FOutlineMap();

	explicit FOutlineMap(AMyGameState* GameState);

	FOutlineMap(UTexture2D* OutlinesMapTexture, UTexture2D* ProvincesMapTexture, AMyGameState* GameState);

	void CreateOutline();

private:
	AMyGameState* GameState;
	
	UTexture2D* OutlinesMapTexture;
	
	UTexture2D* ProvincesMapTexture;

	FVector2D SizeVector;

	FColor OutlineColor = FColor(0, 0, 0);
	
	FColor BackgroundColor = FColor(255, 255, 255);
};
