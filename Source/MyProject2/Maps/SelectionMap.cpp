#include "SelectionMap.h"

#include "MyProject2/TextureUtils.h"

FSelectionMap::FSelectionMap(): GameState(nullptr), SelectionMapTexture(nullptr), ProvincesMapTexture(nullptr)
{
}

FSelectionMap::FSelectionMap(AMyGameState* GameState):
	GameState(GameState),
	SelectionMapTexture(GameState->GetProvinceManager()->GetSelectionMapTexture()),
	ProvincesMapTexture(GameState->GetProvinceManager()->GetProvincesMapTexture())
{
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

FSelectionMap::FSelectionMap(UTexture2D* SelectionMapTexture, UTexture2D* ProvincesMapTexture, AMyGameState* GameState):
	GameState(GameState), SelectionMapTexture(SelectionMapTexture), ProvincesMapTexture(ProvincesMapTexture)
{
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

void FSelectionMap::SelectProvince(const FColor& Color)
{
	if (Color == SelectedProvince) return;

	FColor* SelectionMapColors = FTextureUtils::GetPixels(SelectionMapTexture, LOCK_READ_WRITE);

	const FColor* ProvinceMapColors = FTextureUtils::GetPixels(ProvincesMapTexture, LOCK_READ_ONLY);

	const int Size = SizeVector.X * SizeVector.Y;

	FTextureUtils::UpdateColors(ProvinceMapColors, SelectedProvince, SelectionMapColors, NonSelectedProvinceColor,
	                            Size);

	FTextureUtils::UpdateColors(ProvinceMapColors, Color, SelectionMapColors, SelectedProvinceColor, Size);

	SelectedProvince = Color;

	FTextureUtils::UnlockPixels(SelectionMapTexture);

	FTextureUtils::UnlockPixels(ProvincesMapTexture);

	SelectionMapTexture->UpdateResource();
}

void FSelectionMap::SelectProvince(const FVector2d& Point)
{
	const FColor Color = GetProvinceColor(Point);
	SelectProvince(Color);
}

FColor FSelectionMap::GetProvinceColor(const FVector2d& Point) const
{
	const FVector2d ImagePosition = Point * SizeVector;

	const FColor* Colors = FTextureUtils::GetPixels(ProvincesMapTexture, LOCK_READ_ONLY);

	const FColor Color = Colors[FTextureUtils::GetPixelPosition(ImagePosition, SizeVector)];

	FTextureUtils::UnlockPixels(ProvincesMapTexture);

	return Color;
}
