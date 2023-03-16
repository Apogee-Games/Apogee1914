// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelsOverides/Game/GameLevelGameState.h"

AGameLevelGameState::AGameLevelGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

int AGameLevelGameState::GetStability() const
{
	return Stability;
}

void AGameLevelGameState::SetStability(int32 NewStability)
{
	Stability = NewStability;
}