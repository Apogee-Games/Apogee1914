#pragma once
#include "MyProject2/Maps/Graph.h"
#include "MyProject2/Military/Instances/Unit.h"
#include "MyProject2/Military/Interfaces/Observables/UnitMovementObservable.h"

#include "UnitsMover.generated.h"


UCLASS()
class UUnitsMover: public UWorldSubsystem, public IUnitMovementObservable
{
	GENERATED_BODY()

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	FGraph* GetGraph() const;

	void SetGraph(FGraph* NewGraph);

	virtual void MoveUnit(UUnit* Unit, UProvince* To);

	virtual int Estimate(UUnit* Unit, UProvince* To);

	virtual void DoUnitMovement();
	
private:
	FGraph* Graph = nullptr;

	TMap<UUnit*, TArray<TPair<UProvince*, int>>> Paths;

	TMap<UUnit*, int> Positions;

	TQueue<UUnit*> UnitsArrived;

	void MoveUnit(UUnit* Unit, int Position);

	void RemoveArrivedUnit();

	void MoveUnits();
};