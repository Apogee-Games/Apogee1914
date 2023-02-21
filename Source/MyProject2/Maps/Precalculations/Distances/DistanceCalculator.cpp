#include "DistanceCalculator.h"

FDistanceCalculator::FDistanceCalculator(TArray<int32>& Distances, const FVector2d& SizeVector, int Depth): IDistanceProcessor(Distances, SizeVector, Depth)
{
}

void FDistanceCalculator::AddStartPoint(int Point)
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
	while (!Queue.IsEmpty())
	{
		int32 CurrentPosition;
		
		Queue.Dequeue(CurrentPosition);

		if (Distances[CurrentPosition] >= Depth) continue;
		
		const int y = CurrentPosition / static_cast<int>(SizeVector.Y);
		const int x = CurrentPosition % static_cast<int>(SizeVector.Y);
		
		if (x > 0 && CurrentPosition - 1 >= 0 
			&& Distances[CurrentPosition] + 1 < Distances[CurrentPosition - 1])
		{
			Queue.Enqueue(CurrentPosition - 1);
			Distances[CurrentPosition - 1] = Distances[CurrentPosition] + 1;
		}
		
		if (x + 1 < SizeVector.X && CurrentPosition + 1 < SizeVector.X * SizeVector.Y
			&& Distances[CurrentPosition] + 1 < Distances[CurrentPosition + 1])
		{
			Queue.Enqueue(CurrentPosition + 1);
			Distances[CurrentPosition + 1] = Distances[CurrentPosition] + 1;
		}

		if (y > 0 && CurrentPosition - static_cast<int>(SizeVector.X) >= 0
			&& Distances[CurrentPosition] + 1 < Distances[CurrentPosition - static_cast<int>(SizeVector.X)])
		{
			Queue.Enqueue(CurrentPosition - static_cast<int>(SizeVector.X));
			Distances[CurrentPosition - static_cast<int>(SizeVector.X)] = Distances[CurrentPosition] + 1;
		}
		
		if (y + 1 < SizeVector.Y && CurrentPosition + static_cast<int>(SizeVector.X) < SizeVector.X * SizeVector.Y
			&& Distances[CurrentPosition] + 1 < Distances[CurrentPosition + static_cast<int>(SizeVector.X)])
		{
			Queue.Enqueue(CurrentPosition + static_cast<int>(SizeVector.X));
			Distances[CurrentPosition + static_cast<int>(SizeVector.X)] = Distances[CurrentPosition] + 1;
		}
	}
}
