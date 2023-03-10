#pragma once
#include "Maps/Interfaces/DistanceProcessor.h"

class FDistanceCleaner: public IDistanceProcessor
{
public:
	FDistanceCleaner(TArray<int32>& Distances, const FVector2d& SizeVector, int32 Depth);

	virtual void AddStartPoint(int32 Point) override;
	
	void AddPossiblePoints(const TArray<int32>& Points);

	virtual uint32 Run() override;
private:
	TArray<TArray<int32>> PossiblePoints; // TODO: Use sets
	
	void CleanUpDistances();

	bool IsPossiblePoint(int32 Point);
};
