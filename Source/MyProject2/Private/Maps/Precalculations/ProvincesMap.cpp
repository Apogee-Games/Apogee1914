
#include "Maps/Precalculations/ProvincesMap.h"

#include "Administration/Managers/CountriesManager.h"
#include "Administration/Managers/StateManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Utils/TextureUtils.h"

bool UProvincesMap::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UProvincesMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

void UProvincesMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	PositionColor.SetNum(SizeVector.X * SizeVector.Y);
	
	CalculateMappers(ProvincesMapTexture);
	
	FindNeighbours();

	CalculateBorders();

	bIsFullyInitialized = true;
	PerformOnFullInitializationActions();

	//GetWorld()->GetSubsystem<UProvinceManager>()->AddProvinceControllingCountryObserver(this);
	// TODO: think of order (meaning new controller -> update distances or new owner update distances)
}

FVector2d UProvincesMap::GetSizeVector() const
{
	return SizeVector;
}

const TArray<FColor>& UProvincesMap::GetColors() const
{
	return PositionColor;
}

const TMap<FColor, TSet<FColor>>& UProvincesMap::GetNeighbours() const
{
	return Neighbours;
}

const FColor& UProvincesMap::GetColor(int32 Position) const
{
	return PositionColor[Position];
}

bool UProvincesMap::HasProvincePosition(const FColor& Color) const
{
	return ColorPosition.Contains(Color);
}

const TArray<int32>& UProvincesMap::GetProvincePositions(const FColor& Color) const
{
	return ColorPosition[Color];
}

void UProvincesMap::ProvinceHasNewOwningCountry(UProvince* Province)
{
	// TODO: DO staff :)
	/*UpdateCountriesDistances(Province);
	NotifyCountryDistancesUpdateForProvince(Province);*/
}

void UProvincesMap::Deinitialize()
{
	
	Super::Deinitialize();
}

void UProvincesMap::CalculateMappers(UTexture2D* ProvinceMap)
{
	const FColor* Colors = FTextureUtils::GetPixels(ProvinceMap, LOCK_READ_WRITE);

	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	
	for (int32 i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		PositionColor[i] = FColor(Colors[i]);
		
		if (!ColorPosition.Contains(PositionColor[i])) {
			ColorPosition.Add(PositionColor[i], TArray<int32>());
		}
		
		ColorPosition[PositionColor[i]].Add(i);
	}

	FTextureUtils::UnlockPixels(ProvinceMap);
}

void UProvincesMap::FindNeighbours()
{
	for (const auto& [Color, Positions]: ColorPosition)
	{
		Neighbours.Add(Color);	
	}

	int32 Width = static_cast<int>(SizeVector.X);
	int32 Height = static_cast<int>(SizeVector.Y);
	
	for (int32 i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		const int32 y = i / Width;
		const int32 x = i % Width;
		
		if (x > 0 && PositionColor[i] != PositionColor[i - 1])
		{
			Neighbours[PositionColor[i]].Add(PositionColor[i - 1]);
			Neighbours[PositionColor[i - 1]].Add(PositionColor[i]);
		}
		if (x + 1 < SizeVector.X && PositionColor[i] != PositionColor[i + 1])
		{
			Neighbours[PositionColor[i]].Add(PositionColor[i + 1]);
			Neighbours[PositionColor[i + 1]].Add(PositionColor[i]);
		}
		if (y > 0 && PositionColor[i] != PositionColor[i - Width])
		{
			Neighbours[PositionColor[i]].Add(PositionColor[i - Width]);
			Neighbours[PositionColor[i - Width]].Add(PositionColor[i]);
		}
		if (y + 1 < Height && PositionColor[i] != PositionColor[i + Width])
		{
			Neighbours[PositionColor[i]].Add(PositionColor[i + Width]);
			Neighbours[PositionColor[i + Width]].Add(PositionColor[i]);
		}
	}
}

void UProvincesMap::CalculateBorders()
{
	const int32 Width = static_cast<int32>(SizeVector.X);
	const int32 Height = static_cast<int32>(SizeVector.Y);
	for (int32 i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		const int32 y = i / Width;
		const int32 x = i % Width;
		
		if (x > 0 && PositionColor[i] != PositionColor[i - 1])
		{
			AddBorder(PositionColor[i], PositionColor[i - 1], i);
		}
		if (x + 1 < Width && PositionColor[i] != PositionColor[i + 1])
		{
			AddBorder(PositionColor[i], PositionColor[i + 1], i);
		}
		if (y > 0 && PositionColor[i] != PositionColor[i - Width])
		{
			AddBorder(PositionColor[i], PositionColor[i - Width], i);
		}
		if (y + 1 < Height && PositionColor[i] != PositionColor[i + Width])
		{
			AddBorder(PositionColor[i], PositionColor[i + Width], i);
		}
	}
}

void UProvincesMap::AddBorder(const FColor& A, const FColor& B, int32 i)
{
	if (!Borders.Contains({A, B}))
	{
		Borders.Add({A, B}, TArray<int32>());
		Borders.Add({B, A}, TArray<int32>());
	}
	Borders[{A, B}].Add(i);
	Borders[{B, A}].Add(i);
}
