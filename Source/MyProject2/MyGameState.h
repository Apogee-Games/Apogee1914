// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGameTime.h"
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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;

	FInGameTime* GetInGameTime() const;

	FProvince* GetProvince(const FColor& ProvinceColor) const;

	FColor GetCountryColor(const FColor& ProvinceColor) const;

	FState* GetState(const FString& StateId) const;

	bool AreProvincesInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesNotInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool ExistsCountryWithSuchProvince(const FColor& ProvinceColor) const;

	TArray<FString>* GetCountriesTagsList();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	FDateTime StartTime = FDateTime(1914, 1, 1);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	int MaxTimeSpeed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	float SpeedMultiplier;

	int GetStability() const;

	void SetStability(int Stability);
private:

	UPROPERTY()
	UTexture2D* ProvincesMapTexture;

	UPROPERTY()
	UTexture2D* SelectionMapTexture;

	UPROPERTY()
	UTexture2D* CountriesMapTexture;

	UPROPERTY()
	UTexture2D* OutlinesMapTexture;

	FInGameTime* GameTime;

	TArray<FString> CountriesTagsList;

	int Stability = 0;
};
