// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

AMyGameState::AMyGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

int AMyGameState::GetStability() const
{
	return Stability;
}

void AMyGameState::SetStability(int32 NewStability)
{
	Stability = NewStability;
}