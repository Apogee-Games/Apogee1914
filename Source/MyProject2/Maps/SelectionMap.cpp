#include "SelectionMap.h"

#include "MyProject2/Characters/HumanPlayerPawn.h"
#include "MyProject2/Utils/TextureUtils.h"

void USelectionMap::SelectProvince(const FColor& Color)
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

void USelectionMap::SelectProvince(const FVector2d& Point)
{
	const FColor Color = GetProvinceColor(Point);
	SelectProvince(Color);
}

FColor USelectionMap::GetProvinceColor(const FVector2d& Point) const
{
	const FVector2d ImagePosition = Point * SizeVector;

	const FColor* Colors = FTextureUtils::GetPixels(ProvincesMapTexture, LOCK_READ_ONLY);

	const FColor Color = Colors[FTextureUtils::GetPixelPosition(ImagePosition, SizeVector)];

	FTextureUtils::UnlockPixels(ProvincesMapTexture);

	return Color;
}

void USelectionMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SelectionMapTexture = FTextureUtils::LoadTexture("/Game/maps/province");
	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}