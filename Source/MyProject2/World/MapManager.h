#pragma once
#include "MyProject2/MyGameState.h"
#include "Rendering/Texture2DResource.h"

class FMapManager
{
public:
	FMapManager(const FString& ProvincesMapTexturePath, const FString& BlankMapTexturePath,
	            const FString& CountriesColorsMapTexturePath, const FString& OutlinesMapTexturePath);

	void SetGameState(const AMyGameState* NewGameState);

	void UpdateCountriesMapColors() const;

	FColor GetProvinceColor(const FVector2d& Point) const;

	void Select(const FColor& Color);

	void BeginPlay();
	
private:
	const AMyGameState* GameState;

	UTexture2D* ProvincesMapTexture;

	UTexture2D* BlankMapTexture;

	UTexture2D* CountriesColorsMapTexture;

	UTexture2D* OutlinesMapTexture;

	UTexture2D* CentersMapTexture;

	FVector2d SizeVector;

	const FColor OutlineDefaultColor = FColor(0, 0, 0);

	const FColor DefaultCurrentlySelectedProvinceColor = FColor(75, 75, 150);

	FColor CurrentlySelectedProvinceColor = DefaultCurrentlySelectedProvinceColor;

	TMap<FColor, int> ProvincesCenters;

	void CalculateProvincesCenters();

	void DisplayCenters();

	void CreateOutline();

	static int GetPixelPosition(const FVector2d& ImagePosition, const FVector2d& SizeVector);

	static FVector2d GetPositionVector(int Position, const FVector2d& SizeVector);

	static void UpdateColors(FColor* Colors, const FColor& Old, const FColor& New, const int& Size);

	static void UpdateColors(const FColor* LookUpColors, const FColor& LookUpColor, FColor* EditableColors,
	                         const FColor& NewColor, const int& Size);

	static UTexture2D* LoadTexture(const FString& Path);

	static FVector2d GetTextureSizeVector(const UTexture2D* Texture);

	int GetMapSize() const;

	static FColor* GetPixels(UTexture2D* Texture, uint32 LockFlags);
	
	static void UnlockPixels(UTexture2D* Texture);
};
