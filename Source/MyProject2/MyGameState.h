// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGameTime.h"
#include "GameFramework/GameStateBase.h"

#include "Managers/ProvinceManager.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	FDateTime StartTime = FDateTime(1914, 1, 1);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	int MaxTimeSpeed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	float SpeedMultiplier;

	int GetStability() const;

	void SetStability(int Stability);
	
private:
	FInGameTime* GameTime;
	
	int Stability = 0;
};
