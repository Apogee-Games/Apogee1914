// Fill out your copyright notice in the Description page of Project Settings.


#include "Maps/Diplomacy/CountryRelationMapUpdater.h"

FCountryRelationMapUpdater::FCountryRelationMapUpdater(const TArray<int32>& ProvincePositions, FColor* Colors, FColor Color): ProvincePositions(ProvincePositions), Colors(Colors), Color(Color)
{
		
}

uint32 FCountryRelationMapUpdater::Run()
{
	for (const int32 Position: ProvincePositions)
	{
		Colors[Position] = Color;
	}
	
	return 0;
}
