#include "UnitsMover.h"

FGraph* UUnitsMover::GetGraph() const
{
	return Graph;
}

void UUnitsMover::SetGraph(FGraph* NewGraph)
{
	Graph = NewGraph;
}

void UUnitsMover::MoveUnit(UUnit* Unit, const FColor& Province)
{
	TArray<TPair<FColor, int>> Path = Graph->FindPath(Unit->GetPosition(), Province);
	Paths.Add(Unit, Path);
}

int UUnitsMover::Estimate(UUnit* Unit, const FColor& Province)
{
	const TArray<TPair<FColor, int>> Path = Graph->FindPath(Unit->GetPosition(), Province);
	return Unit->Estimate(Path);
}

void UUnitsMover::Tick()
{
	TSet<UUnit*> UnitsArrived;	
	for (const auto& Pair: Positions)
	{
		Paths[Pair.Key][Pair.Value].Value--;
		if (Paths[Pair.Key][Pair.Value].Value == 0)
		{
			Pair.Key->Move(Paths[Pair.Key][Pair.Value].Key);
			Positions[Pair.Key]++;
		}
		if (Positions[Pair.Key] >= Paths[Pair.Key].Num()) UnitsArrived.Add(Pair.Key);
	}
	for (const auto& Unit: UnitsArrived)
	{
		Paths.Remove(Unit);
		Positions.Remove(Unit);
	}
}
