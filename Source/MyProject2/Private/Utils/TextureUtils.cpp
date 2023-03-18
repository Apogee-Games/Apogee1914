#include "Utils/TextureUtils.h"


int32 FTextureUtils::GetPixelPosition(const FVector2d& ImagePosition, const FVector2d& SizeVector)
{
	return static_cast<int32>(ImagePosition.X) + SizeVector.X * static_cast<int32>(ImagePosition.Y);
}

FVector2d FTextureUtils::GetPositionVector(int32 Position, const FVector2d& SizeVector)
{
	return FVector2d(Position % static_cast<int32>(SizeVector.X), Position / SizeVector.X);
}

void FTextureUtils::UpdateColors(FColor* Colors, const FColor& Old, const FColor& New, const int32& Size)
{
	for (int32 i = 0; i < Size; ++i)
	{
		if (Colors[i] == Old) Colors[i] = FColor(New);
	}
}

void FTextureUtils::UpdateColors(const FColor* LookUpColors, const FColor& LookUpColor, FColor* EditableColors,
							   const FColor& NewColor, const int32& Size)
{
	for (int32 i = 0; i < Size; ++i)
	{
		if (LookUpColors[i] == LookUpColor) EditableColors[i] = FColor(NewColor);
	}
}

UTexture2D* FTextureUtils::LoadTexture(const FString& Path)
{
	return LoadObject<UTexture2D>(nullptr, *Path);
}

FVector2d FTextureUtils::GetTextureSizeVector(const UTexture2D* Texture)
{
	return FVector2d(Texture->GetImportedSize().X, Texture->GetImportedSize().Y);
}

FColor* FTextureUtils::GetPixels(UTexture2D* Texture, uint32 LockFlags)
{
	return static_cast<FColor*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LockFlags));
}

void FTextureUtils::UnlockPixels(UTexture2D* Texture)
{
	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
}
