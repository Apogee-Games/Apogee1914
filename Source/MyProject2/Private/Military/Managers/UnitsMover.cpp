
#include "Military/Managers/UnitsMover.h"

#include "InGameTime.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Maps/MapsDataGatherer.h"

void UUnitsMover::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

const FGraph& UUnitsMover::GetGraph() const
{
	return Graph;
}

void UUnitsMover::MoveUnit(UUnit* Unit, UProvince* To)
{
	if (RetreatingUnits.Contains(Unit)) return;
	const TArray<FPathElement>& Path = Graph.FindPath(Unit->GetPosition(), To);
	if (!Path.IsEmpty())
	{
		Paths.Add(Unit, Path);
		Positions.Add(Unit, 0);
		Unit->SetIsUnitMoving(true);
	}
}

void UUnitsMover::MoveUnits(const TSet<UUnit*>& Units, UProvince* To)
{
	for (const auto& Unit: Units)
	{
		MoveUnit(Unit, To);
	}
}

void UUnitsMover::MoveUnits(const TArray<UUnit*>& Units, UProvince* To)
{
	for (const auto& Unit: Units)
	{
		MoveUnit(Unit, To);
	}
}

void UUnitsMover::MoveUnits(const TSet<UUnitsCollection*>& UnitsCollections, UProvince* To)
{
	for (const auto& UnitsCollection: UnitsCollections)
	{
		MoveUnits(UnitsCollection->GetAll(), To);
	}
}

void UUnitsMover::MoveUnits(const TSet<UUnitsCollectionGroup*>& UnitsCollectionGroups, UProvince* To)
{
	for (const auto& UnitsCollectionsGroup: UnitsCollectionGroups)
	{
		MoveUnits(UnitsCollectionsGroup->GetAll(), To);
	}
}

void UUnitsMover::MoveUnits(const TMap<UMilitaryBranchDescription*, FUnitsSelection>& Selections, UProvince* To)
{
	for (const auto& [MilitaryBranch, Selection]: Selections)
	{
		MoveUnits(Selection.SelectedUnits, To);
		MoveUnits(Selection.SelectedUnitsCollections, To);
		MoveUnits(Selection.SelectedUnitsCollectionGroups, To);
	}
}

int32 UUnitsMover::Estimate(UUnit* Unit, UProvince* To)
{
	const TArray<FPathElement> Path = Graph.FindPath(Unit->GetPosition(), To);
	return Unit->Estimate(Path);
}

void UUnitsMover::DoUnitMovement()
{
	MoveUnits();
	RemoveArrivedUnit();
}

void UUnitsMover::SuspendMovement(UUnit* Unit)
{
	SuspendedUnits.Add(Unit);
}

void UUnitsMover::UnSuspendMovement(UUnit* Unit)
{
	SuspendedUnits.Remove(Unit);
	if (Paths[Unit][Positions[Unit]].Cost == 0)
	{
		Paths.Remove(Unit);
		Positions.Remove(Unit);
	}
}

bool UUnitsMover::Retreat(UUnit* Unit)
{
	TArray<FPathElement> Path = Graph.CreateRetreatPath(Unit->GetPosition(), Unit->GetCountryController());
	if (!Path.IsEmpty())
	{
		Paths.Add(Unit, Path);
		Positions.Add(Unit, 0);
		RetreatingUnits.Add(Unit);
	}
	return !Path.IsEmpty();
}

ELoadStage UUnitsMover::GetLoadStage()
{
	return ELoadStage::UnitsMover;
}

void UUnitsMover::Clear()
{
	Paths.Empty();
	Positions.Empty();
	UnitsArrived.Empty();
}

void UUnitsMover::Init(UScenario* Scenario)
{
	UGameInstance* GameInstance = GetGameInstance();
	Graph = FGraph(GameInstance->GetSubsystem<UMapsDataGatherer>()->GetNeighbourProvinces(), GameInstance->GetSubsystem<UMapsDataGatherer>());
	GameInstance->GetSubsystem<UInGameTime>()->RegisterListener(this, &UUnitsMover::DoUnitMovement, UnitMoveTimeDelta);
}

void UUnitsMover::RemoveArrivedUnit()
{
	while (!UnitsArrived.IsEmpty())
	{
		UUnit* Unit;
		UnitsArrived.Dequeue(Unit);
		if (SuspendedUnits.Contains(Unit)) continue;
		Paths.Remove(Unit);
		Positions.Remove(Unit);
		RetreatingUnits.Remove(Unit);
	}
}

void UUnitsMover::MoveUnits()
{
	for (const auto& [Unit, Position]: Positions)
	{
		if (SuspendedUnits.Contains(Unit)) continue;
		Paths[Unit][Position].Cost--;
		if (Paths[Unit][Position].Cost == 0)
		{
			OnUnitMoved.Broadcast(Unit, Unit->GetPosition(), Paths[Unit][Position].To);

			Unit->Move(Paths[Unit][Position].To);
			Positions[Unit]++;
			if (Positions[Unit] >= Paths[Unit].Num()) UnitsArrived.Enqueue(Unit);
		}
	}
}
