// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
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
	AMyGameState();

	int GetStability() const;

	void SetStability(int32 Stability);
private:
	int32 Stability = 0;
};
