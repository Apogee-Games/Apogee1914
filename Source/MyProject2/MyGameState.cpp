// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

#include "MyProject2/Utils/TextureUtils.h"

AMyGameState::AMyGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");

	SelectionMapTexture = FTextureUtils::LoadTexture("/Game/maps/province");

	CountriesMapTexture = FTextureUtils::LoadTexture("/Game/maps/country");

	OutlinesMapTexture = FTextureUtils::LoadTexture("/Game/maps/outlines");
}

void AMyGameState::BeginPlay()
{
	GameTime = new FInGameTime(&StartTime, MaxTimeSpeed, SpeedMultiplier);
	ProvinceManager = NewObject<UProvinceManager>();
	Super::BeginPlay();
}

void AMyGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	delete GameTime;
	Super::EndPlay(EndPlayReason);
}

void AMyGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!GameTime->IsGamePaused())
	{
		GameTime->UpdateCurrentTime(DeltaSeconds * 1000);
	}
}

FInGameTime* AMyGameState::GetInGameTime() const
{
	return GameTime;
}

UProvinceManager* AMyGameState::GetProvinceManager() const
{
	return ProvinceManager;
}

UTexture2D* AMyGameState::GetProvincesMapTexture() const
{
	return ProvincesMapTexture;
}

UTexture2D* AMyGameState::GetSelectionMapTexture() const
{
	return SelectionMapTexture;
}

UTexture2D* AMyGameState::GetCountriesMapTexture() const
{
	return CountriesMapTexture;
}

UTexture2D* AMyGameState::GetOutlinesMapTexture() const
{
	return OutlinesMapTexture;
}

int AMyGameState::GetStability() const
{
	return Stability;
}

void AMyGameState::SetStability(int NewStability)
{
	Stability = NewStability;
}