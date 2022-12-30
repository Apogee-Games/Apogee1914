#pragma once
#include "MyProject2/MyGameState.h"
#include "Rendering/Texture2DResource.h"

class FMapManager
{
public:
	FMapManager(const FString& ProvincesMapTexturePath, const FString& BlankMapTexturePath,  const FString& CountriesColorsMapTexturePath, const FString& OutlinesMapTexturePath):
		GameState(nullptr)
	{
		ProvincesMapTexture = LoadTexture(ProvincesMapTexturePath);
		BlankMapTexture = LoadTexture(BlankMapTexturePath);
		CountriesColorsMapTexture = LoadTexture(CountriesColorsMapTexturePath);
		OutlinesMapTexture = LoadTexture(OutlinesMapTexturePath);
		SizeVector = GetTextureSizeVector(ProvincesMapTexture);
		CreateOutline();
	}

	void SetGameState(const AMyGameState* NewGameState)
	{
		GameState = NewGameState;
	}
	
	void UpdateCountriesMapColors() const
	{
		const FColor* ProvincesColors = static_cast<const FColor*>(ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.LockReadOnly());

		FColor* CountriesColors = static_cast<FColor*>(CountriesColorsMapTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		
		for (int i = 0; i < GetMapSize(); ++i)
		{
			CountriesColors[i] = GameState->GetCountryColor(ProvincesColors[i]);
		}
		
		CountriesColorsMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

		CountriesColorsMapTexture->UpdateResource();

		ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

	}
	
	FColor GetProvinceColor(const FVector2d& Point) const
	{
		const FVector2d ImagePosition = Point * SizeVector;

		const FColor* Colors = static_cast<const FColor*>(ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.
			LockReadOnly());

		const FColor Color = Colors[GetPixelPosition(ImagePosition, SizeVector)];

		ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

		return Color;
	}

	void Select(const FColor& Color)
	{
		if (Color == CurrentlySelectedProvinceColor) return;

		FColor* BlankMapColors = static_cast<FColor*>(BlankMapTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

		const FColor* ProvinceMapColors = static_cast<const FColor*>(ProvincesMapTexture->GetPlatformData()->Mips[0].
		                                                             BulkData.LockReadOnly());

		UpdateColors(ProvinceMapColors, CurrentlySelectedProvinceColor, BlankMapColors, FColor(0, 0, 0, 0), GetMapSize());

		UpdateColors(ProvinceMapColors, Color, BlankMapColors, DefaultCurrentlySelectedProvinceColor, GetMapSize());

		CurrentlySelectedProvinceColor = Color;

		BlankMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

		ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

		BlankMapTexture->UpdateResource();
	}

	void operator=(const FMapManager& MapManager);

private:
	const AMyGameState* GameState;
	
	UTexture2D* ProvincesMapTexture;

	UTexture2D* BlankMapTexture;
	
	UTexture2D* CountriesColorsMapTexture;
	
	UTexture2D* OutlinesMapTexture;

	FVector2d SizeVector;

	const FColor DefaultCurrentlySelectedProvinceColor = FColor(75, 75, 150);

	FColor CurrentlySelectedProvinceColor = DefaultCurrentlySelectedProvinceColor;

	void CreateOutline()
	{
		FColor* OutlineColors = static_cast<FColor*>(OutlinesMapTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		const FColor* ProvincesColor = static_cast<const FColor*>(ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.LockReadOnly());
		
		for (int i = 0; i < GetMapSize(); ++i)
		{
			int y = i / static_cast<int>(SizeVector.Y);
			int x = i % static_cast<int>(SizeVector.Y);
			if (x > 0 && ProvincesColor[i] != ProvincesColor[i - 1])
			{
				OutlineColors[i] = FColor(0, 0, 0);
				continue;
			}
			if (x + 1 < SizeVector.X && ProvincesColor[i] != ProvincesColor[i + 1])
			{
				OutlineColors[i] = FColor(0, 0, 0);
				continue;
			}
			
			if (y > 0 && ProvincesColor[i] != ProvincesColor[i - static_cast<int>(SizeVector.X)])
			{
				OutlineColors[i] = FColor(0, 0, 0);
				continue;
			}
			if (y + 1 < SizeVector.Y && ProvincesColor[i] != ProvincesColor[i + 1])
			{
				OutlineColors[i] = FColor(0, 0, 0);
				continue;
			}
			OutlineColors[i] = FColor(255, 255, 255);
		}
		
		OutlinesMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
		ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

		OutlinesMapTexture->UpdateResource();
	}

	static int GetPixelPosition(const FVector2d& ImagePosition, const FVector2d& SizeVector)
	{
		return static_cast<int>(ImagePosition.X) + SizeVector.X * static_cast<int>(ImagePosition.Y);
	}

	static void UpdateColors(FColor* Colors, const FColor& Old, const FColor& New, const int& Size)
	{
		for (int i = 0; i < Size; ++i)
		{
			if (Colors[i] == Old) Colors[i] = FColor(New);
		}
	}

	static void UpdateColors(const FColor* LookUpColors, const FColor& LookUpColor, FColor* EditableColors,
	                         const FColor& NewColor, const int& Size)
	{
		for (int i = 0; i < Size; ++i)
		{
			if (LookUpColors[i] == LookUpColor) EditableColors[i] = FColor(NewColor);
		}
	}

	static UTexture2D* LoadTexture(const FString& Path)
	{
		return ConstructorHelpers::FObjectFinder<UTexture2D>(*Path).Object;
	}

	static FVector2d GetTextureSizeVector(const UTexture2D* Texture)
	{
		return FVector2d(Texture->GetSizeX(), Texture->GetSizeY());
	}

	int GetMapSize() const
	{
		return SizeVector.X * SizeVector.Y;
	}
};
