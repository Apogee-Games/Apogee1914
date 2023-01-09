// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

AMyGameState::AMyGameState()
{
	ProvinceManager = NewObject<UProvinceManager>();
}

UProvinceManager* AMyGameState::GetProvinceManager() const
{
	return ProvinceManager;
}

