#pragma once

class IDistanceProcessor: public FRunnable
{
public:
	IDistanceProcessor(TArray<int32>& Distances, const FVector2d& SizeVector, int32 Depth);

	virtual void AddStartPoint(int32 Point);

protected:
	TQueue<int32> Queue;

	TArray<int32>& Distances;

	const FVector2d SizeVector;

	int32 Depth;

};