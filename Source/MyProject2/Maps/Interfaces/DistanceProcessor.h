#pragma once

class IDistanceProcessor: public FRunnable
{
public:
	IDistanceProcessor(int* Distances, const FVector2d& SizeVector, int Depth);

	virtual void AddStartPoint(int Point);

protected:
	TQueue<int32> Queue;

	int* Distances;

	const FVector2d SizeVector;

	int Depth;

};