#pragma once
#include "MyProject2/Maps/Interfaces/DistanceProcessor.h"

class FDistanceCalculator: public IDistanceProcessor
{
public:
	FDistanceCalculator(TArray<int32>& Distances, const FVector2d& SizeVector, int32 Depth);

	virtual void AddStartPoint(int32 Point) override;
	
	virtual uint32 Run() override;

private:
	void CalculateDistances();
};

