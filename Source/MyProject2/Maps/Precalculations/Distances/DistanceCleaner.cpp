#include "DistanceCleaner.h"


FDistanceCleaner::FDistanceCleaner(int* Distances, const FVector2d& SizeVector, int Depth): IDistanceProcessor(Distances, SizeVector, Depth)
{
}

void FDistanceCleaner::AddStartPoint(int Point)
{
	IDistanceProcessor::AddStartPoint(Point);
	Distances[Point] = Depth;

}

void FDistanceCleaner::AddPossiblePoints(const TArray<int32>& Points)
{
	PossiblePoints.Add(Points);
}

uint32 FDistanceCleaner::Run()
{
	CleanUpDistances();
	return 0;
}

void FDistanceCleaner::CleanUpDistances()
{
	while (!Queue.IsEmpty())
	{
		int32 CurrentPosition;
		
		Queue.Dequeue(CurrentPosition);

		if (!IsPossiblePoint(CurrentPosition))
		{
			continue;
		}
		
		const int y = CurrentPosition / static_cast<int>(SizeVector.Y);
		const int x = CurrentPosition % static_cast<int>(SizeVector.Y);
		
		if (x > 0 && CurrentPosition - 1 >= 0
			&& Distances[CurrentPosition - 1] < Depth)
		{
			Distances[CurrentPosition - 1] = Depth;
			Queue.Enqueue(CurrentPosition - 1);
		}
		
		if (x + 1 < SizeVector.X && CurrentPosition + 1 < SizeVector.X * SizeVector.Y
			&& Distances[CurrentPosition + 1] < Depth)
		{
			Distances[CurrentPosition + 1] = Depth;
			Queue.Enqueue(CurrentPosition + 1);
		}

		if (y > 0 && CurrentPosition - static_cast<int>(SizeVector.X) >= 0
			&& Distances[CurrentPosition - static_cast<int>(SizeVector.X)] < Depth)
		{
			Distances[CurrentPosition - static_cast<int>(SizeVector.X)] = Depth;
			Queue.Enqueue(CurrentPosition - static_cast<int>(SizeVector.X));
		}
		
		if (y + 1 < SizeVector.Y && CurrentPosition + static_cast<int>(SizeVector.X) < SizeVector.X * SizeVector.Y
			&& Distances[CurrentPosition + static_cast<int>(SizeVector.X)] < Depth)
		{
			Distances[CurrentPosition + static_cast<int>(SizeVector.X)] = Depth;
			Queue.Enqueue(CurrentPosition + static_cast<int>(SizeVector.X));
		}
	}
}

bool FDistanceCleaner::IsPossiblePoint(int Point)
{
	for (const auto& Points: PossiblePoints)
	{
		if (Points.Contains(Point))
		{
			return true;
		}
	}
	return false;
}
