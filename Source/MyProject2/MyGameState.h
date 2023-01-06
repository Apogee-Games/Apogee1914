// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Engine/DataTable.h"
#include "World/Country.h"
#include "World/Province.h"
#include "World/State.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMyGameState();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void UpdateCurrentTime(float DeltaSeconds);

	FDateTime* GetTime();
	
	FProvince* GetProvince(const FColor& ProvinceColor) const;

	FColor GetCountryColor(const FColor& ProvinceColor) const;

	FState* GetState(const FString& StateId) const;

	bool AreProvincesInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const;
	
	bool AreProvincesNotInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const;

	bool IsGamePaused() const;

	void PauseGame();

	void ResumeGame();

	void SwitchPauseFlag();
	
	UTexture2D* GetProvincesMapTexture() const;

	UTexture2D* GetSelectionMapTexture() const;

	UTexture2D* GetCountriesMapTexture() const;

	UTexture2D* GetOutlinesMapTexture() const;

	void SpeedUpTime();

	void SlowDownTime();

	UPROPERTY()
	UDataTable* CountryDescriptionDataTable;

	UPROPERTY()
	UDataTable* ProvinceDescriptionDataTable;

	UPROPERTY()
	UDataTable* StateDescriptionDataTable;

private:
	UPROPERTY()
	UTexture2D* ProvincesMapTexture;

	UPROPERTY()
	UTexture2D* SelectionMapTexture;

	UPROPERTY()
	UTexture2D* CountriesMapTexture;

	UPROPERTY()
	UTexture2D* OutlinesMapTexture;

	FDateTime* CurrentTime;

	bool bIsGamePaused = true;
	
	int TimeSpeed = 1;
};
