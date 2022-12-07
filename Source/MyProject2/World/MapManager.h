#pragma once

class FMapManager
{
public:
	FMapManager(const FString& ProvincesMapPath)
	{
		Texture = LoadTexture(ProvincesMapPath);
	}

	FColor GetProvinceColor(const FVector2d& Point) const
	{
		const FVector2d ImagePosition = Point * FVector2d(Texture->GetSizeX(), Texture->GetSizeY());

		const FColor* Colors = static_cast<const FColor*>(Texture->GetPlatformData()->Mips[0].BulkData.LockReadOnly());

		const FColor Color = Colors[(int)ImagePosition.X + Texture->GetSizeX() * (int)ImagePosition.Y];

		Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

		return Color;
	}

	void Select(const FColor& Color)
	{
		FColor* Colors = static_cast<FColor*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

		ResetProvinceColor(Colors);

		UpdateColors(Colors, Color, DefaultCurrentlySelectedProvinceColor, GetTextureSize(Texture));

		CurrentlySelectedProvinceColor = Color;

		Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

		Texture->UpdateResource();
	}

private:
	UTexture2D* Texture;

	FColor CurrentlySelectedProvinceColor = FColor(0, 0, 255);

	const FColor DefaultCurrentlySelectedProvinceColor = FColor(200, 50, 50);

	void ResetProvinceColor(FColor* Colors) const
	{
		if (DefaultCurrentlySelectedProvinceColor == CurrentlySelectedProvinceColor) return;
		UpdateColors(Colors,
		             DefaultCurrentlySelectedProvinceColor,
		             CurrentlySelectedProvinceColor,
		             GetTextureSize(Texture));
	}

	static int GetTextureSize(const UTexture2D* Texture)
	{
		return Texture->GetSizeX() * Texture->GetSizeY();
	}

	static UTexture2D* LoadTexture(const FString& Path)
	{
		return ConstructorHelpers::FObjectFinder<UTexture2D>(*Path).Object;
	}

	static void UpdateColors(FColor* Colors, const FColor& Old, const FColor& New, const int& Size)
	{
		for (int i = 0; i < Size; ++i)
		{
			if (Colors[i] == Old) Colors[i] = FColor(New);
		}
	}
};
