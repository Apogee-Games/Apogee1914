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
	Positions.Add(Unit, 0);
}

int UUnitsMover::Estimate(UUnit* Unit, const FColor& Province)
{
	const TArray<TPair<FColor, int>> Path = Graph->FindPath(Unit->GetPosition(), Province);
	return Unit->Estimate(Path);
}

void UUnitsMover::Tick()
{
	// TODO: Add logic for movement of Unit that is already being moved
	// TODO: Add Tick to be triggered every day (or whatever smallest time unit we will have)
	MoveUnits();
	RemoveArrivedUnit();
}

void UUnitsMover::MoveUnit(UUnit* Unit, int Position)
{
	NotifyUnitMovement(Unit, Unit->GetPosition(), Paths[Unit][Position].Key);
	Unit->Move(Paths[Unit][Position].Key);
	Positions[Unit]++;
	if (Positions[Unit] >= Paths[Unit].Num()) UnitsArrived.Enqueue(Unit);
}

void UUnitsMover::RemoveArrivedUnit()
{
	while (!UnitsArrived.IsEmpty())
	{
		UUnit* Unit;
		UnitsArrived.Dequeue(Unit);
		Paths.Remove(Unit);
		Positions.Remove(Unit);
	}
}

void UUnitsMover::MoveUnits()
{
	for (const auto& [Unit, Position]: Positions)
	{
		Paths[Unit][Position].Value--;
		if (Paths[Unit][Position].Value == 0)
		{
			MoveUnit(Unit, Position);	
		}
	}
}
