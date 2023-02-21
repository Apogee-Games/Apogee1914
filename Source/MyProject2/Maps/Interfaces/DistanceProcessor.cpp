#include "DistanceProcessor.h"

IDistanceProcessor::IDistanceProcessor(TArray<int32>& Distances, const FVector2d& SizeVector, int Depth): Distances(Distances), SizeVector(SizeVector), Depth(Depth)
{
}

void IDistanceProcessor::AddStartPoint(int Point)
{
	Queue.Enqueue(Point);
}
