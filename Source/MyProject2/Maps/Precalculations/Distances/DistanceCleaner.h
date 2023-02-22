#pragma once
#include "MyProject2/Maps/Interfaces/DistanceProcessor.h"

class FDistanceCleaner: public IDistanceProcessor
{
public:
	FDistanceCleaner(int* Distances, const FVector2d& SizeVector, int Depth);

	virtual void AddStartPoint(int Point) override;
	
	void AddPossiblePoints(const TArray<int32>& Points);

	virtual uint32 Run() override;
private:
	TArray<TArray<int32>> PossiblePoints; // TODO: Use sets
	
	void CleanUpDistances();

	bool IsPossiblePoint(int Point);
};
