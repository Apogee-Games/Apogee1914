// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Widgets/Military/Map/UnitInformationListWidget.h"

#include "GameLevelGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AGameLevelGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AGameLevelGameState();

	int GetStability() const;

	void SetStability(int32 Stability);
private:
	int32 Stability = 0;
};
