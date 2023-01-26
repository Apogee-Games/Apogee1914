// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

AMyGameState::AMyGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameState::BeginPlay()
{
	GameTime = new FInGameTime(&StartTime, MaxTimeSpeed, SpeedMultiplier);
	Super::BeginPlay();
}

void AMyGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	delete GameTime;
	Super::EndPlay(EndPlayReason);
}

void AMyGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!GameTime->IsGamePaused())
	{
		GameTime->UpdateCurrentTime(DeltaSeconds * 1000);
	}
}

FInGameTime* AMyGameState::GetInGameTime() const
{
	return GameTime;
}

int AMyGameState::GetStability() const
{
	return Stability;
}

void AMyGameState::SetStability(int NewStability)
{
	Stability = NewStability;
}