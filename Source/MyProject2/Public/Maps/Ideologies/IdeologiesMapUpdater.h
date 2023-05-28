// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class FIdeologiesMapUpdater : public FRunnable
{
public:
	FIdeologiesMapUpdater(const TArray<int32>& Positions, FColor* Colors, FColor Color);

	virtual uint32 Run() override;
private:
	const TArray<int32>& Positions;

	FColor* Colors;

	FColor Color;
};
