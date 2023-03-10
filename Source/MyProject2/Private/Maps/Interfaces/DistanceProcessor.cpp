
#include "Maps/Interfaces/DistanceProcessor.h"

IDistanceProcessor::IDistanceProcessor(TArray<int32>& Distances, const FVector2d& SizeVector, int32 Depth): Distances(Distances), SizeVector(SizeVector), Depth(Depth)
{
}

void IDistanceProcessor::AddStartPoint(int32 Point)
{
	Queue.Enqueue(Point);
}
