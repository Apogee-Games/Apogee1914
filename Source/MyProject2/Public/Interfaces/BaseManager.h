#pragma once
#include "BaseManager.generated.h"

UENUM()
enum class ELoadStage: int32
{
	Initial = 0,

	InGameTime,

	LawsManager,
	PeopleManager,
	CountriesManager,
	ProvinceManager,
	StateManager,

	ProvincesMap,
	DistancesMap,
	BoxesMap,
	OutlineMap,
	ObjectMap,
	FlagsMap,
	CountriesMap,
	SelectionMap,

	CountryRelationMap,
	AlliancesMap,

	RelationshipsManager,
	IdeologiesMap,
	MapsSwitcher,

	GoodsManager,
	StrataManager,
	BuildingManager,

	UnitsFactory,
	UnitsMover,
	CommandersManager,
	UnitsSupplyController,
	BattlesManager,

	ConditionsCheckingSubsystem,
	EventInstancesController,
	OutcomesApplierSubsystem,

	Finished
};

UCLASS(Abstract, Blueprintable)
class UBaseManager: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario)
	{
		
	}
	
	virtual ELoadStage GetLoadStage()
	{
		return ELoadStage::Initial;
	}
};
