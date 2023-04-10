#pragma once

class FTextureUtils
{
public:
	static int32 GetPixelPosition(const FVector2d& ImagePosition, const FVector2d& SizeVector);

	static FVector2d GetPositionVector(int32 Position, const FVector2d& SizeVector);

	static void UpdateColors(FColor* Colors, const FColor& Old, const FColor& New, const int32& Size);

	static void UpdateColors(const FColor* LookUpColors, const FColor& LookUpColor, FColor* EditableColors,
							 const FColor& NewColor, const int32& Size);

	static UTexture2D* LoadTexture(const FString& Path);

	static FVector2d GetTextureSizeVector(const UTexture2D* Texture);

	static FVector2d GetTextureSizeVector(const UTexture2DDynamic* Texture);
	
	static FColor* GetPixels(UTexture2D* Texture, uint32 LockFlags);
	
	static void UnlockPixels(UTexture2D* Texture);
	static void UnlockPixels(UTexture2DDynamic* Texture);
};
