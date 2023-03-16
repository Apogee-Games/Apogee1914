
#include "Military/Managers/UnitsMover.h"

#include "InGameTime.h"
#include "Administration/Managers/ProvinceManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

bool UUnitsMover::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UUnitsMover::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UUnitsMover::DoUnitMovement, UnitMoveTimeDelta);
}

FGraph* UUnitsMover::GetGraph() const
{
	return Graph;
}

void UUnitsMover::SetGraph(FGraph* NewGraph)
{
	Graph = NewGraph;
}

void UUnitsMover::MoveUnit(UUnit* Unit, UProvince* To)
{
	const TArray<TPair<UProvince*, int32>> Path = Graph->FindPath(Unit->GetPosition(), To);
	Paths.Add(Unit, Path);
	Positions.Add(Unit, 0);
}

int32 UUnitsMover::Estimate(UUnit* Unit, UProvince* To)
{
	const TArray<TPair<UProvince*, int32>> Path = Graph->FindPath(Unit->GetPosition(), To);
	return Unit->Estimate(Path);
}

void UUnitsMover::DoUnitMovement()
{
	MoveUnits();
	RemoveArrivedUnit();
}

void UUnitsMover::MoveUnit(UUnit* Unit, int32 Position)
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
