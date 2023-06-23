
#include "Maps/Precalculations/ProvincesMap.h"

#include "CanvasTypes.h"
#include "MyGameInstance.h"
#include "Administration/Managers/CountriesManager.h"
#include "Administration/Managers/StateManager.h"
#include "Engine/TextureRenderTarget2D.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Utils/TextureUtils.h"

void UProvincesMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

FVector2d UProvincesMap::GetSizeVector() const
{
	return SizeVector;
}

const TArray<FColor>& UProvincesMap::GetColors() const
{
	return PositionColor;
}

const TMap<FColor, TSet<FColor>>& UProvincesMap::GetNeighbourColors() const
{
	return NeighbourColors;
}

const TMap<UProvince*, TSet<UProvince*>>& UProvincesMap::GetNeighbourProvinces()
{
	return NeighbourProvinces;
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
	if (!ColorPosition.Contains(Color))
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, Color.ToHex());
		}

		static TArray<int32> Array;
		return Array;
	}
	return ColorPosition[Color];
}

void UProvincesMap::ProvinceHasNewOwningCountry(UProvince* Province)
{
	// TODO: DO staff :)
	/*UpdateCountriesDistances(Province);
	NotifyCountryDistancesUpdateForProvince(Province);*/
}

ELoadStage UProvincesMap::GetLoadStage()
{
	return ELoadStage::ProvincesMap;
}

void UProvincesMap::CalculateMappers(UTexture2D* ProvinceMap)
{
	const FColor* Colors = FTextureUtils::GetPixels(ProvinceMap, LOCK_READ_WRITE);

	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	
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
		NeighbourColors.Add(Color);	
	}

	int32 Width = static_cast<int>(SizeVector.X);
	int32 Height = static_cast<int>(SizeVector.Y);
	
	for (int32 i = 0; i < SizeVector.X * SizeVector.Y; ++i)
	{
		const int32 y = i / Width;
		const int32 x = i % Width;
		
		if (x > 0 && PositionColor[i] != PositionColor[i - 1])
		{
			NeighbourColors[PositionColor[i]].Add(PositionColor[i - 1]);
			NeighbourColors[PositionColor[i - 1]].Add(PositionColor[i]);
		}
		if (x + 1 < SizeVector.X && PositionColor[i] != PositionColor[i + 1])
		{
			NeighbourColors[PositionColor[i]].Add(PositionColor[i + 1]);
			NeighbourColors[PositionColor[i + 1]].Add(PositionColor[i]);
		}
		if (y > 0 && PositionColor[i] != PositionColor[i - Width])
		{
			NeighbourColors[PositionColor[i]].Add(PositionColor[i - Width]);
			NeighbourColors[PositionColor[i - Width]].Add(PositionColor[i]);
		}
		if (y + 1 < Height && PositionColor[i] != PositionColor[i + Width])
		{
			NeighbourColors[PositionColor[i]].Add(PositionColor[i + Width]);
			NeighbourColors[PositionColor[i + Width]].Add(PositionColor[i]);
		}
	}

	// TODO: Think of uniting this two types
	
	UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();

	for (const auto& [Color, DirectNeighboursColors]: NeighbourColors)
	{
		UProvince* Province = ProvinceManager->GetProvince(Color);
		if (!Province) continue;;

		TSet<UProvince*> ProvinceDirectNeighbours;
		for (const auto& ColorB: DirectNeighboursColors)
		{
			UProvince* ProvinceB = ProvinceManager->GetProvince(ColorB);
			if (!ProvinceB) continue;

			ProvinceDirectNeighbours.Add(ProvinceB);
		}
		NeighbourProvinces.Add(Province, ProvinceDirectNeighbours);
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

void UProvincesMap::Clear()
{
	ProvincesMapTexture = nullptr;
	ColorPosition.Empty();
	NeighbourColors.Empty();
	Borders.Empty();
	PositionColor.Empty();
}

void UProvincesMap::Init(UScenario* Scenario)
{
	ProvincesMapTexture = Scenario->ProvincesMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);

	UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	const TArray<UProvince*>& Provinces = ProvinceManager->GetAllProvinces();

	UTextureRenderTarget2D* ProvincesIdsLookUpTexture = Scenario->ProvincesIdsLookUpTexture;
	ProvincesIdsLookUpTexture->ResizeTarget(Provinces.Num(), 256);

	FCanvas CanvasProvincesIdsLookUpTexture(ProvincesIdsLookUpTexture->GameThread_GetRenderTargetResource(), nullptr, GetWorld(), ERHIFeatureLevel::SM5);
	
	for (int i = 0; i < Provinces.Num(); ++i)
	{
		CanvasProvincesIdsLookUpTexture.DrawTile(i, 0, 1, 256, 0, 0, 1, 1, Provinces[i]->GetId());
	}

	CanvasProvincesIdsLookUpTexture.Flush_GameThread(true);

	UTextureRenderTarget2D* CountriesColorsLookUpTexture = Scenario->CountriesColorsLookUpTexture;
	CountriesColorsLookUpTexture->ResizeTarget(Provinces.Num(), 256);

	FCanvas CanvasCountriesColorsLookUpTexture(CountriesColorsLookUpTexture->GameThread_GetRenderTargetResource(), nullptr, GetWorld(), ERHIFeatureLevel::SM5);
	
	for (int i = 0; i < Provinces.Num(); ++i)
	{
		CanvasCountriesColorsLookUpTexture.DrawTile(i, 0, 1, 256, 0, 0, 1, 1, Provinces[i]->GetCountryController()->GetColor());
	}

	CanvasCountriesColorsLookUpTexture.Flush_GameThread(true);
	
	PositionColor.SetNum(SizeVector.X * SizeVector.Y);
	
	CalculateMappers(ProvincesMapTexture);
	
	FindNeighbours();

	CalculateBorders();
	
	//GetGameInstance()->GetSubsystem<UProvinceManager>()->AddProvinceControllingCountryObserver(this);
	// TODO: think of order (meaning new controller -> update distances or new owner update distances)
}
