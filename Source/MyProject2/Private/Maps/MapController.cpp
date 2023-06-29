// Fill out your copyright notice in the Description page of Project Settings.


#include "Maps/MapController.h"

#include "CanvasTypes.h"
#include "Administration/Instances/Country.h"
#include "Administration/Instances/Province.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Maps/MapsDataGatherer.h"
#include "Utils/TextureUtils.h"

void UMapController::SetScenario(UScenario* Scenario)
{
	Super::SetScenario(Scenario);
	Clear();
	Init(Scenario);
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

	UGameInstance* GameInstance = GetGameInstance();
	FColor Color = GameInstance->GetSubsystem<UMapsDataGatherer>()->GetColor(Position);

	return GameInstance->GetSubsystem<UProvinceManager>()->GetProvince(Color);
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
	
}

void UMapController::Init(UScenario* Scenario)
{
	AsyncTask(ENamedThreads::GameThread, [this, Scenario]()
	{
		SelectionHighlight = Scenario->SelectionHighlight;
		NonAlignedCountryColor = Scenario->NonAlignedCountryColor;
		NonAlliedCountryColor = Scenario->NonAlliedCountryColor;
		ColorsMapping = Scenario->ColorsMapping;
		
		Provinces = GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces();
		SizeVector = FTextureUtils::GetTextureSizeVector(Scenario->ProvincesMapTexture);

		DrawProvincesIdsMap(Scenario->ProvincesIdsLookUpTexture);

		Canvas = MakeUnique<FCanvas>(Scenario->ProvincesColorsLookUpTexture->GameThread_GetRenderTargetResource(), nullptr, GetWorld(), ERHIFeatureLevel::SM5);
		Scenario->ProvincesColorsLookUpTexture->ResizeTarget(Provinces.Num(), 1);

		SetCountriesMapAll();
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