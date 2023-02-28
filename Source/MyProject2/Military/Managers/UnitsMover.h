#pragma once
#include "MyProject2/Maps/Graph.h"
#include "MyProject2/Military/Instances/Units/Unit.h"
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

	virtual void MoveUnit(FUnit* Unit, UProvince* To);

	virtual int32 Estimate(FUnit* Unit, UProvince* To);

	virtual void DoUnitMovement();
	
private:
	FGraph* Graph = nullptr;

	TMap<FUnit*, TArray<TPair<UProvince*, int32>>> Paths;

	TMap<FUnit*, int32> Positions;

	TQueue<FUnit*> UnitsArrived;

	void MoveUnit(FUnit* Unit, int32 Position);

	void RemoveArrivedUnit();

	void MoveUnits();
};