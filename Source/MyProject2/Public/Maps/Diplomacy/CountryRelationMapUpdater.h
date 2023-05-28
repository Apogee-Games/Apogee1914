// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class FCountryRelationMapUpdater : public FRunnable
{
public:
	FCountryRelationMapUpdater(const TArray<int32>& ProvincePositions, FColor* Colors, FColor Color);

	virtual uint32 Run() override;
private:
	const TArray<int32>& ProvincePositions;

	FColor* Colors;

	FColor Color;
};
