#include "DistanceCleaner.h"


FDistanceCleaner::FDistanceCleaner(TArray<int32>& Distances, const FVector2d& SizeVector, int32 Depth): IDistanceProcessor(Distances, SizeVector, Depth)
{
}

void FDistanceCleaner::AddStartPoint(int32 Point)
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
	const int32 Width = static_cast<int32>(SizeVector.X);
	const int32 Height = static_cast<int32>(SizeVector.Y);
	while (!Queue.IsEmpty())
	{
		int32 CurrentPosition;
		
		Queue.Dequeue(CurrentPosition);

		if (!IsPossiblePoint(CurrentPosition))
		{
			continue;
		}
		
		const int32 y = CurrentPosition / Width;
		const int32 x = CurrentPosition % Width;
		
		if (x > 0 && CurrentPosition - 1 >= 0
			&& Distances[CurrentPosition - 1] < Depth)
		{
			Distances[CurrentPosition - 1] = Depth;
			Queue.Enqueue(CurrentPosition - 1);
		}
		
		if (x + 1 < Width && Distances[CurrentPosition + 1] < Depth)
		{
			Distances[CurrentPosition + 1] = Depth;
			Queue.Enqueue(CurrentPosition + 1);
		}

		if (y > 0 && Distances[CurrentPosition - Width] < Depth)
		{
			Distances[CurrentPosition - Width] = Depth;
			Queue.Enqueue(CurrentPosition - Width);
		}
		
		if (y + 1 < Height && Distances[CurrentPosition + Width] < Depth)
		{
			Distances[CurrentPosition + Width] = Depth;
			Queue.Enqueue(CurrentPosition + Width);
		}
	}
}

bool FDistanceCleaner::IsPossiblePoint(int32 Point)
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
