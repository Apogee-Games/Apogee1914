#include "MapManager.h"

FMapManager::FMapManager(const FString& ProvincesMapTexturePath, const FString& BlankMapTexturePath,
	const FString& CountriesColorsMapTexturePath, const FString& OutlinesMapTexturePath):
	GameState(nullptr)
{
	ProvincesMapTexture = LoadTexture(ProvincesMapTexturePath);
	BlankMapTexture = LoadTexture(BlankMapTexturePath);
	CountriesColorsMapTexture = LoadTexture(CountriesColorsMapTexturePath);
	OutlinesMapTexture = LoadTexture(OutlinesMapTexturePath);
	SizeVector = GetTextureSizeVector(ProvincesMapTexture);
	CentersMapTexture = LoadTexture("/Game/maps/Centers");
	CreateOutline();
}

void FMapManager::SetGameState(const AMyGameState* NewGameState)
{
	GameState = NewGameState;
}

void FMapManager::UpdateCountriesMapColors() const
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

FColor FMapManager::GetProvinceColor(const FVector2d& Point) const
{
	const FVector2d ImagePosition = Point * SizeVector;

	const FColor* Colors = static_cast<const FColor*>(ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.
		LockReadOnly());

	const FColor Color = Colors[GetPixelPosition(ImagePosition, SizeVector)];

	ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

	return Color;
}

void FMapManager::Select(const FColor& Color)
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

void FMapManager::CalculateProvincesCenters()
{
	TMap<FColor, unsigned long long> Counts;
	TMap<FColor, FVector2d> Sums;

	const FColor* Colors = static_cast<const FColor*>(ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.LockReadOnly());

	for (unsigned long long i = 0; i < GetMapSize(); ++i)
	{
		if (!Counts.Contains(Colors[i])) Counts.Add(Colors[i],0);
		if (!Sums.Contains(Colors[i])) Sums.Add(Colors[i], FVector2d(0, 0));
		Counts[Colors[i]]++;
		Sums[Colors[i]] += GetPositionVector(i, SizeVector);
	}
		
	for (FColor ProvinceColor: GameState->GetProvincesColors())
	{
		const FVector2d Center = Sums[ProvinceColor] / Counts[ProvinceColor];
		ProvincesCenters.Add(ProvinceColor, GetPixelPosition(Center, SizeVector));
	}

	ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

}

void FMapManager::DisplayCenters()
{
	FColor* Colors = static_cast<FColor*>(CentersMapTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		
	for (const auto Pair: ProvincesCenters)
	{
		Colors[Pair.Value - 2] = FColor(255,0,0);
		Colors[Pair.Value - 1] = FColor(255,0,0);
		Colors[Pair.Value] = FColor(255,0,0);
		Colors[Pair.Value + 1] = FColor(255,0,0);
		Colors[Pair.Value + 2] = FColor(255,0,0);
	}

	CentersMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

	CentersMapTexture->UpdateResource();
}

void FMapManager::CreateOutline()
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
			OutlineColors[i] = OutlineDefaultColor;
			continue;
		}
			
		if (y > 0 && ProvincesColor[i] != ProvincesColor[i - static_cast<int>(SizeVector.X)])
		{
			OutlineColors[i] = OutlineDefaultColor;
			continue;
		}
		if (y + 1 < SizeVector.Y && ProvincesColor[i] != ProvincesColor[i + 1])
		{
			OutlineColors[i] = OutlineDefaultColor;
			continue;
		}
		OutlineColors[i] = FColor(255, 255, 255);
	}
		
	OutlinesMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
	ProvincesMapTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
		
	OutlinesMapTexture->UpdateResource();
		
}

int FMapManager::GetPixelPosition(const FVector2d& ImagePosition, const FVector2d& SizeVector)
{
	return static_cast<int>(ImagePosition.X) + SizeVector.X * static_cast<int>(ImagePosition.Y);
}

FVector2d FMapManager::GetPositionVector(int Position, const FVector2d& SizeVector)
{
	return FVector2d(Position % static_cast<int>(SizeVector.X), Position / SizeVector.X);
}

void FMapManager::UpdateColors(FColor* Colors, const FColor& Old, const FColor& New, const int& Size)
{
	for (int i = 0; i < Size; ++i)
	{
		if (Colors[i] == Old) Colors[i] = FColor(New);
	}
}

void FMapManager::UpdateColors(const FColor* LookUpColors, const FColor& LookUpColor, FColor* EditableColors,
	const FColor& NewColor, const int& Size)
{
	for (int i = 0; i < Size; ++i)
	{
		if (LookUpColors[i] == LookUpColor) EditableColors[i] = FColor(NewColor);
	}
}

UTexture2D* FMapManager::LoadTexture(const FString& Path)
{
	return ConstructorHelpers::FObjectFinder<UTexture2D>(*Path).Object;
}

FVector2d FMapManager::GetTextureSizeVector(const UTexture2D* Texture)
{
	return FVector2d(Texture->GetSizeX(), Texture->GetSizeY());
}

int FMapManager::GetMapSize() const
{
	return SizeVector.X * SizeVector.Y;
}
