#include "TextureUtils.h"


int FTextureUtils::GetPixelPosition(const FVector2d& ImagePosition, const FVector2d& SizeVector)
{
	return static_cast<int>(ImagePosition.X) + SizeVector.X * static_cast<int>(ImagePosition.Y);
}

FVector2d FTextureUtils::GetPositionVector(int Position, const FVector2d& SizeVector)
{
	return FVector2d(Position % static_cast<int>(SizeVector.X), Position / SizeVector.X);
}

void FTextureUtils::UpdateColors(FColor* Colors, const FColor& Old, const FColor& New, const int& Size)
{
	for (int i = 0; i < Size; ++i)
	{
		if (Colors[i] == Old) Colors[i] = FColor(New);
	}
}

void FTextureUtils::UpdateColors(const FColor* LookUpColors, const FColor& LookUpColor, FColor* EditableColors,
							   const FColor& NewColor, const int& Size)
{
	for (int i = 0; i < Size; ++i)
	{
		if (LookUpColors[i] == LookUpColor) EditableColors[i] = FColor(NewColor);
	}
}

UTexture2D* FTextureUtils::LoadTexture(const FString& Path)
{
	return ConstructorHelpers::FObjectFinder<UTexture2D>(*Path).Object;
}

FVector2d FTextureUtils::GetTextureSizeVector(const UTexture2D* Texture)
{
	return FVector2d(Texture->GetSizeX(), Texture->GetSizeY());
}


FColor* FTextureUtils::GetPixels(UTexture2D* Texture, uint32 LockFlags)
{
	return static_cast<FColor*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LockFlags));
}

void FTextureUtils::UnlockPixels(UTexture2D* Texture)
{
	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
}
