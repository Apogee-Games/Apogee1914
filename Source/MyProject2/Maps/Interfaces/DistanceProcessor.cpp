#include "DistanceProcessor.h"

IDistanceProcessor::IDistanceProcessor(int* Distances, const FVector2d& SizeVector, int Depth): Distances(Distances), SizeVector(SizeVector), Depth(Depth)
{
}

void IDistanceProcessor::AddStartPoint(int Point)
{
	Queue.Enqueue(Point);
}
