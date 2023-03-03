// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Widgets/Events/EventWidget.h"
#include "Widgets/Military/Map/UnitInformationListWidget.h"

#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	// TODO: Move widget classes to HUD :)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEventWidget> EventWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUnitInformationListWidget> UnitInformationListWidgetClass;

	// TODO: Extract to respective class
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan MinDeltaBetweenEventChecks = FTimespan(24, 0, 0);

	// TODO: Extract to respective class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	FDateTime StartTime = FDateTime(1914, 1, 1);

	// TODO: Extract to respective class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	int MaxTimeSpeed = 5;

	// TODO: Extract to respective class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	float SpeedMultiplier = 0.1;
	
	AMyGameState();

	int GetStability() const;

	void SetStability(int32 Stability);
private:
	int32 Stability = 0;
};
