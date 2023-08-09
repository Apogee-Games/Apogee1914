// Fill out your copyright notice in the Description page of Project Settings.


#include "Maps/MapController.h"

#include "CanvasTypes.h"
#include "Administration/Instances/Country.h"
#include "Administration/Instances/Province.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Diplomacy/Instances/Alliance.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Maps/MapsDataGatherer.h"
#include "Military/Managers/UnitsFactory.h"
#include "Utils/TextureUtils.h"

void UMapController::SetScenario(UScenario* Scenario)
{
	Super::SetScenario(Scenario);
	Clear();
	Init(Scenario);
}

void UMapController::SetMapMode(EMapMode MapMode)
{
	switch (MapMode)
	{
	case EMapMode::AlliancesMap: SetAlliancesMapAll(); break;
	case EMapMode::IdeologiesMap: SetIdeologiesMapAll(); break;
	case EMapMode::CountriesMap: SetCountriesMapAll(); break;
	case EMapMode::RelationsMap: SetCountryRelationMapAll(); break;
	}
}

void UMapController::SetCountriesMapAll()
{
	ColorGetter = [this](UProvince* Province)
	{
		return Province->GetOwnerCountry()->GetColor().ReinterpretAsLinear();
	};
	RefreshLookUpTexture();
}

void UMapController::SetAlliancesMapAll()
{
	ColorGetter = [this](UProvince* Province)
	{
		const UCountry* Country = Province->GetCountryController();
		if (Country->IsNonAligned()) return NonAlignedCountryColor;
		if (!Country->IsInAlliance()) return NonAlliedCountryColor;
		return Country->GetAlliance()->GetColor();
	};
	RefreshLookUpTexture();
}

void UMapController::SetCountryRelationMapAll()
{
	ColorGetter = [this](UProvince* Province)
	{
		APlayerController* Controller = GetGameInstance()->GetFirstLocalPlayerController();
		AHumanPlayerPawn* Pawn = Controller->GetPawn<AHumanPlayerPawn>();
		UCountry* Country = Pawn->GetRuledCountry();
		return ColorsMapping[Country->GetRelation(Province->GetCountryController())];
	};
	RefreshLookUpTexture();
}

void UMapController::SetIdeologiesMapAll()
{
	ColorGetter = [this](UProvince* Province)
	{
		return Province->GetCountryController()->GetIdeology()->Color;
	};
	RefreshLookUpTexture();
}

void UMapController::SelectProvince(UProvince* Province)
{
	for (int i = 0; i < Provinces.Num(); ++i)
	{
		if (Provinces[i] == Province) {
			Canvas->DrawTile(i, 0, 1, 1, 0, 0, 1, 1, ColorGetter(Province) + SelectionHighlight);

			if (SelectedProvinceIndex != INDEX_NONE)
			{
				Canvas->DrawTile(SelectedProvinceIndex, 0, 1, 1, 0, 0, 1, 1, ColorGetter(Provinces[SelectedProvinceIndex]));
			}

			SelectedProvinceIndex = i;
		}
	}
	Canvas->Flush_GameThread(true);
}

UProvince* UMapController::GetProvince(FVector2d Point)
{
	const FVector2d ImagePosition = Point * SizeVector;
	const int32 Position = FTextureUtils::GetPixelPosition(ImagePosition, SizeVector);

	FColor Color = MapsDataGatherer->GetColor(Position);

	return GetGameInstance()->GetSubsystem<UProvinceManager>()->GetProvince(Color);
}

UProvince* UMapController::SelectProvince(FVector2d Point)
{
	UProvince* Province = GetProvince(Point);
	SelectProvince(Province);
	return Province;
}

void UMapController::RefreshLookUpTexture()
{
	for (int i = 0; i < Provinces.Num(); ++i)
	{
		if (i == SelectedProvinceIndex) {
			Canvas->DrawTile(i, 0, 1, 1, 0, 0, 1, 1, ColorGetter(Provinces[i]) + SelectionHighlight);
		}
		else
		{
			Canvas->DrawTile(i, 0, 1, 1, 0, 0, 1, 1, ColorGetter(Provinces[i]));

		}
	}
	Canvas->Flush_GameThread(true);
}

void UMapController::SetOutlineEnabled(bool InbOutlineEnabled)
{
	bOutlineEnabled = InbOutlineEnabled;
	// TODO: Pass to material instance
}

ELoadStage UMapController::GetLoadStage()
{
	return ELoadStage::MapController;
}

void UMapController::Clear()
{
	MapItems.Empty();
}

void UMapController::Init(UScenario* Scenario)
{
	AsyncTask(ENamedThreads::GameThread, [this, Scenario]()
	{
		UGameInstance* GameInstance = GetGameInstance();

		MapsDataGatherer = GameInstance->GetSubsystem<UMapsDataGatherer>();
		UnitsFactory = GameInstance->GetSubsystem<UUnitsFactory>();
		
		SelectionHighlight = Scenario->SelectionHighlight;
		NonAlignedCountryColor = Scenario->NonAlignedCountryColor;
		NonAlliedCountryColor = Scenario->NonAlliedCountryColor;
		ColorsMapping = Scenario->RelationsColors;
		
		Provinces = GameInstance->GetSubsystem<UProvinceManager>()->GetAllProvinces();
		SizeVector = FTextureUtils::GetTextureSizeVector(Scenario->ProvincesMapTexture);

		DrawProvincesIdsMap(Scenario->ProvincesIdsLookUpTexture);

		Canvas = MakeUnique<FCanvas>(Scenario->ProvincesColorsLookUpTexture->GameThread_GetRenderTargetResource(), nullptr, GetWorld(), ERHIFeatureLevel::SM5);
		Scenario->ProvincesColorsLookUpTexture->ResizeTarget(Provinces.Num(), 1);

		SetCountriesMapAll();

		// TODO: Remove this hard code and add save/load
		
		MapItems.Init(EMapMode::None, 5);
		MapItems[0] = EMapMode::CountriesMap;
		SelectedMapItem = 0;

		bOutlineEnabled = false;

		MiniMapCanvas = MakeUnique<FCanvas>(Scenario->MiniMapTexture->GameThread_GetRenderTargetResource(), nullptr, GetWorld(), ERHIFeatureLevel::SM5);
		MiniMapSizeVector.X = Scenario->MiniMapTexture->SizeX;
		MiniMapSizeVector.Y = Scenario->MiniMapTexture->SizeY;

		MiniMapClearColor = Scenario->MiniMapTexture->ClearColor;
		
		MiniMapColors = Scenario->MiniMapColors;
	});
}

void UMapController::DrawProvincesIdsMap(UTextureRenderTarget2D* ProvincesIdsLookUpTexture)
{
	ProvincesIdsLookUpTexture->ResizeTarget(Provinces.Num(), 1);

	FCanvas CanvasProvincesIdsLookUpTexture(ProvincesIdsLookUpTexture->GameThread_GetRenderTargetResource(), nullptr, GetWorld(), ERHIFeatureLevel::SM5);
	for (int i = 0; i < Provinces.Num(); ++i)
	{
		CanvasProvincesIdsLookUpTexture.DrawTile(i, 0, 1, 1, 0, 0, 1, 1, Provinces[i]->GetId().ReinterpretAsLinear(), nullptr);
	}
			
	CanvasProvincesIdsLookUpTexture.Flush_GameThread(true);
}

void UMapController::RefreshMiniMap()
{
	if (AHumanPlayerPawn* Pawn = GetGameInstance()->GetFirstLocalPlayerController()->GetPawn<AHumanPlayerPawn>())
	{
		if (UCountry* PlayerCountry = Pawn->GetRuledCountry())
		{
			MiniMapCanvas->Clear(MiniMapClearColor);
			for (UUnit* Unit: UnitsFactory->GetUnits())
			{
				FColor Color = MiniMapColors[Unit->GetCountryController()->GetRelation(PlayerCountry)];
				FVector2d UnitPosition = MapsDataGatherer->GetProvinceCenter(Unit->GetPosition());
				FVector2d Position = UnitPosition * MiniMapSizeVector;
				MiniMapCanvas->DrawTile(Position.X - 4, Position.Y - 4, 8, 8, 0, 0, 1, 1, Color);
			}
			MiniMapCanvas->Flush_GameThread(true);
		}
	}
}