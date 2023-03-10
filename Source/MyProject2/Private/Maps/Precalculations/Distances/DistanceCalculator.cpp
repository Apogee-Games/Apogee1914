
#include "Maps/Precalculations/Distances/DistanceCalculator.h"

FDistanceCalculator::FDistanceCalculator(TArray<int32>& Distances, const FVector2d& SizeVector, int32 Depth): IDistanceProcessor(Distances, SizeVector, Depth)
{
}

void FDistanceCalculator::AddStartPoint(int32 Point)
{
	IDistanceProcessor::AddStartPoint(Point);
	Distances[Point] = 0;
}

uint32 FDistanceCalculator::Run()
{
	CalculateDistances();
	return 0;
}

void FDistanceCalculator::CalculateDistances()
{
	const int32 Width = static_cast<int32>(SizeVector.X);
	const int32 Height = static_cast<int32>(SizeVector.Y);
	while (!Queue.IsEmpty())
	{
		int32 CurrentPosition;
		
		Queue.Dequeue(CurrentPosition);

		if (Distances[CurrentPosition] >= Depth) continue;
		
		const int32 y = CurrentPosition / Width;
		const int32 x = CurrentPosition % Width;
		
		if (x > 0 && Distances[CurrentPosition] + 1 < Distances[CurrentPosition - 1])
		{
			Queue.Enqueue(CurrentPosition - 1);
			Distances[CurrentPosition - 1] = Distances[CurrentPosition] + 1;
		}
		
		if (x + 1 < Width && Distances[CurrentPosition] + 1 < Distances[CurrentPosition + 1])
		{
			Queue.Enqueue(CurrentPosition + 1);
			Distances[CurrentPosition + 1] = Distances[CurrentPosition] + 1;
		}

		if (y > 0&& Distances[CurrentPosition] + 1 < Distances[CurrentPosition - Width])
		{
			Queue.Enqueue(CurrentPosition - Width);
			Distances[CurrentPosition - Width] = Distances[CurrentPosition] + 1;
		}
		
		if (y + 1 < SizeVector.Y && Distances[CurrentPosition] + 1 < Distances[CurrentPosition + Width])
		{
			Queue.Enqueue(CurrentPosition + Width);
			Distances[CurrentPosition + Width] = Distances[CurrentPosition] + 1;
		}
	}
}
