// Fill out your copyright notice in the Description page of Project Settings.


#include "Maps/Ideologies/IdeologiesMapUpdater.h"

FIdeologiesMapUpdater::FIdeologiesMapUpdater(const TArray<int32>& Positions, FColor* Colors, FColor Color): Positions(Positions), Colors(Colors), Color(Color)
{
		
}

uint32 FIdeologiesMapUpdater::Run()
{
	for (const auto& Position: Positions)
	{
		Colors[Position] = Color;
	}
	
	return 0;
}
