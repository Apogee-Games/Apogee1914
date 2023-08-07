#pragma once
#include "Scenario.h"
#include "Characters/Components/UnitsSelectionComponent.h"
#include "Maps/Graph.h"
#include "Military/Instances/Units/Unit.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "Interfaces/BaseManager.h"
#include "UnitsMover.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUnitMoved, UUnit*, UProvince*, UProvince*)

UCLASS(Abstract, Blueprintable)
class UUnitsMover: public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	const FGraph& GetGraph() const;

	virtual void MoveUnit(UUnit* Unit, UProvince* To);

	virtual void MoveUnits(const TSet<UUnit*>& Units, UProvince* To);
	virtual void MoveUnits(const TArray<UUnit*>& Units, UProvince* To);
	virtual void MoveUnits(const TSet<UUnitsCollection*>& UnitsCollections, UProvince* To);
	virtual void MoveUnits(const TSet<UUnitsCollectionGroup*>& UnitsCollectionGroups, UProvince* To);
	virtual void MoveUnits(const TMap<UMilitaryBranchDescription*, FUnitsSelection>& Selections, UProvince* To);
	
	virtual int32 Estimate(UUnit* Unit, UProvince* To);

	virtual void DoUnitMovement();
	
	void SuspendMovement(UUnit* Unit);
	void UnSuspendMovement(UUnit* Unit);

	bool Retreat(UUnit* Unit);

	virtual ELoadStage GetLoadStage() override;

	UPROPERTY(EditDefaultsOnly)
	FTimespan UnitMoveTimeDelta = FTimespan(1, 0, 0);

	FOnUnitMoved OnUnitMoved;
private:
	FGraph Graph;

	TMap<UUnit*, TArray<FPathElement>> Paths;

	UPROPERTY()
	TMap<UUnit*, int32> Positions;

	UPROPERTY()
	TSet<UUnit*> RetreatingUnits;

	TQueue<UUnit*> UnitsArrived;

	UPROPERTY()
	TSet<UUnit*> SuspendedUnits;

	void Clear();

	void Init(UScenario* Scenario);

	void RemoveArrivedUnit();

	void MoveUnits();
};
