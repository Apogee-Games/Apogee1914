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

	FProvince* GetProvince(const FColor& ProvinceColor) const;

	FColor GetCountryColor(const FColor& ProvinceColor) const;

	FState* GetState(const FString& StateId) const;

	bool AreProvincesInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const;
	
	bool AreProvincesNotInTheSameState(FColor ProvinceAColor, FColor ProvinceBColor) const;

	UTexture2D* GetProvincesMapTexture() const;

	UTexture2D* GetSelectionMapTexture() const;

	UTexture2D* GetCountriesMapTexture() const;

	UTexture2D* GetOutlinesMapTexture() const;

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
};

