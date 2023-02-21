#pragma once
#include "MyProject2/Maps/Interfaces/DistanceProcessor.h"

class FDistanceCalculator: public IDistanceProcessor
{
public:
	FDistanceCalculator(int* Distances, const FVector2d& SizeVector, int Depth);

	virtual void AddStartPoint(int Point) override;
	
	virtual uint32 Run() override;

private:
	void CalculateDistances();
};

