#include "DistanceCalculator.h"

FDistanceCalculator::FDistanceCalculator(int* Distances, const FVector2d SizeVector): Distances(Distances), SizeVector(SizeVector)
{
}

void FDistanceCalculator::AddStartPoint(int Position)
{
	Queue.Enqueue(Position);
	Distances[Position] = 0;
}

uint32 FDistanceCalculator::Run()
{
	CalculateDistances(Queue, Distances, SizeVector);
	return 0;
}

void FDistanceCalculator::CalculateDistances(TQueue<int32>& Queue, int* Distances, const FVector2d SizeVector)
{
	while (!Queue.IsEmpty())
	{
		int32 CurrentPosition;
		
		Queue.Dequeue(CurrentPosition);

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
