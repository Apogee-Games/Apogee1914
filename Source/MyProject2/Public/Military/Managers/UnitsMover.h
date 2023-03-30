#pragma once
#include "Characters/Components/UnitsSelectionComponent.h"
#include "Maps/Graph.h"
#include "Military/Instances/Units/Unit.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "Military/Interfaces/Observables/UnitMovementObservable.h"
#include "UnitsMover.generated.h"

UCLASS(Abstract, Blueprintable)
class UUnitsMover: public UWorldSubsystem, public IUnitMovementObservable
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	FGraph* GetGraph() const;

	void SetGraph(FGraph* NewGraph);

	virtual void MoveUnit(UUnit* Unit, UProvince* To);

	virtual void MoveUnits(const TSet<UUnit*>& Units, UProvince* To);

	virtual void MoveUnits(const TSet<UUnitsCollection*>& UnitsCollections, UProvince* To);

	virtual void MoveUnits(const TSet<UUnitsCollectionGroup*>& UnitsCollectionGroups, UProvince* To);

	virtual void MoveUnits(const TArray<FUnitsSelection>& Selections, UProvince* To);
	
	virtual int32 Estimate(UUnit* Unit, UProvince* To);

	virtual void DoUnitMovement();

	UPROPERTY(EditDefaultsOnly)
	FTimespan UnitMoveTimeDelta = FTimespan(1, 0, 0);
	
private:
	FGraph* Graph = nullptr;

	TMap<UUnit*, TArray<TPair<UProvince*, int32>>> Paths;

	UPROPERTY()
	TMap<UUnit*, int32> Positions;

	TQueue<UUnit*> UnitsArrived;

	void MoveUnit(UUnit* Unit, int32 Position);

	void RemoveArrivedUnit();

	void MoveUnits();
};
