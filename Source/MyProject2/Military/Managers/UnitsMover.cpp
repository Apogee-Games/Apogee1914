#include "UnitsMover.h"

#include "MyProject2/InGameTime.h"
#include "MyProject2/Administration/Managers/ProvinceManager.h"

void UUnitsMover::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UUnitsMover::DoUnitMovement, FTimespan(1, 0, 0));
}

FGraph* UUnitsMover::GetGraph() const
{
	return Graph;
}

void UUnitsMover::SetGraph(FGraph* NewGraph)
{
	Graph = NewGraph;
}

void UUnitsMover::MoveUnit(FUnit* Unit, UProvince* To)
{
	const TArray<TPair<UProvince*, int32>> Path = Graph->FindPath(Unit->GetPosition(), To);
	Paths.Add(Unit, Path);
	Positions.Add(Unit, 0);
}

int32 UUnitsMover::Estimate(FUnit* Unit, UProvince* To)
{
	const TArray<TPair<UProvince*, int32>> Path = Graph->FindPath(Unit->GetPosition(), To);
	return Unit->Estimate(Path);
}

void UUnitsMover::DoUnitMovement()
{
	MoveUnits();
	RemoveArrivedUnit();
}

void UUnitsMover::MoveUnit(FUnit* Unit, int32 Position)
{
	NotifyUnitMovement(Unit, Unit->GetPosition(), Paths[Unit][Position].Key);
	Unit->Move(Paths[Unit][Position].Key);
	GetWorld()->GetSubsystem<UProvinceManager>()->UnitMovedIn(Paths[Unit][Position].Key, Unit);
	Positions[Unit]++;
	if (Positions[Unit] >= Paths[Unit].Num()) UnitsArrived.Enqueue(Unit);
}

void UUnitsMover::RemoveArrivedUnit()
{
	while (!UnitsArrived.IsEmpty())
	{
		FUnit* Unit;
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
