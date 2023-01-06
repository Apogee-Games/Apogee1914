// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

#include "TextureUtils.h"

AMyGameState::AMyGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	
	const ConstructorHelpers::FObjectFinder<UDataTable> ProvincesDescriptionFinder(TEXT("/Game/Sources/provinces_description"));
	if (ProvincesDescriptionFinder.Succeeded())
	{
		ProvinceDescriptionDataTable = ProvincesDescriptionFinder.Object;
	}

	const ConstructorHelpers::FObjectFinder<UDataTable> CountriesDescriptionFinder(TEXT("/Game/Sources/countries_description"));
	if (CountriesDescriptionFinder.Succeeded())
	{
		CountryDescriptionDataTable = CountriesDescriptionFinder.Object;
	}
		
	const ConstructorHelpers::FObjectFinder<UDataTable> StateDescriptionFinder(TEXT("/Game/Sources/states_description"));
	if (StateDescriptionFinder.Succeeded())
	{
		StateDescriptionDataTable = StateDescriptionFinder.Object;
	}

	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");

	SelectionMapTexture = FTextureUtils::LoadTexture("/Game/maps/province");

	CountriesMapTexture = FTextureUtils::LoadTexture("/Game/maps/country");

	OutlinesMapTexture = FTextureUtils::LoadTexture("/Game/maps/outlines");
}

void AMyGameState::BeginPlay()
{
	CurrentTime = new FDateTime(1914, 1, 1);
	Super::BeginPlay();
}

void AMyGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bIsGamePaused) {
		UpdateCurrentTime(DeltaSeconds * 1000);
	}
}

void AMyGameState::UpdateCurrentTime(float DeltaSeconds)
{
	(*CurrentTime) += FTimespan(0, DeltaSeconds * TimeSpeed / 5, 0);
}

FDateTime* AMyGameState::GetTime()
{
	return CurrentTime;
}

FProvince* AMyGameState::GetProvince(const FColor& ProvinceColor) const
{
	if (ProvinceColor == FColor(0, 0, 0) || ProvinceColor == FColor(255, 255, 255)) return nullptr;
	return reinterpret_cast<FProvince*>(ProvinceDescriptionDataTable->FindRowUnchecked(FName(ProvinceColor.ToHex())));
}

FColor AMyGameState::GetCountryColor(const FColor& ProvinceColor) const
{
	if (ProvinceColor == FColor(0, 0, 0) || ProvinceColor == FColor(255, 255, 255)) return FColor(20, 20, 20);
	const FProvince* Province = reinterpret_cast<FProvince*>(ProvinceDescriptionDataTable->FindRowUnchecked(FName(ProvinceColor.ToHex())));
	if (!Province) return FColor(20, 20, 20);

	const FCountry* Country = reinterpret_cast<FCountry*>(CountryDescriptionDataTable->FindRowUnchecked(FName(Province->CountryTag)));
	return Country ? Country->Color : FColor(20, 20, 20);
}

FState* AMyGameState::GetState(const FString& StateId) const
{
	return reinterpret_cast<FState*>(StateDescriptionDataTable->FindRowUnchecked(FName(StateId)));
}

bool AMyGameState::AreProvincesInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const
{
	const FProvince* ProvinceA = GetProvince(ProvinceAColor);
	const FProvince* ProvinceB = GetProvince(ProvinceBColor);
	return ProvinceA && ProvinceB && ProvinceA->StateId == ProvinceB->StateId;

}

bool AMyGameState::AreProvincesNotInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const
{
	const FProvince* ProvinceA = GetProvince(ProvinceAColor);
	const FProvince* ProvinceB = GetProvince(ProvinceBColor);
	return ProvinceA && ProvinceB && ProvinceA->StateId != ProvinceB->StateId;
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

void AMyGameState::SpeedUpTime()
{
	if (TimeSpeed >= 9) return;
	++TimeSpeed;
}

void AMyGameState::SlowDownTime()
{
	if (TimeSpeed <= 1) return;
	--TimeSpeed;
}

inline bool AMyGameState::IsGamePaused() const
{
	return bIsGamePaused;
}

void AMyGameState::PauseGame()
{
	bIsGamePaused = true;
}

void AMyGameState::ResumeGame()
{
	bIsGamePaused = false;
}

void AMyGameState::SwitchPauseFlag()
{
	bIsGamePaused = !bIsGamePaused;
}

