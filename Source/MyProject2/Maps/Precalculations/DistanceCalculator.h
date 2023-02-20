#pragma once

class FDistanceCalculator: public FRunnable
{
public:
	FDistanceCalculator(int* Distances, const FVector2d SizeVector);

	void AddStartPoint(int Position);

	virtual uint32 Run() override;

private:
	TQueue<int32> Queue;
	
	int* Distances;
	
	const FVector2d SizeVector;

	static void CalculateDistances(TQueue<int32>& Queue, int* Distances, const FVector2d SizeVector);
};
