// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UProvinceManager* GetProvinceManager() const;

private:

	UPROPERTY()
	UProvinceManager* ProvinceManager;
};

