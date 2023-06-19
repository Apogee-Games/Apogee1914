#pragma once
#include "Scenario.h"
#include "Economics/Instances/Buildings/Building.h"
#include "Economics/Interfaces/Observables/BuildingCreationObservable.h"
#include "Interfaces/BaseManager.h"
#include "BuildingManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UBuildingManager: public UBaseManager, public IBuildingCreationObservable
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	UBuilding* BuildBuilding(UBuildingDescription* Description, UProvince* Province);

	void Tick();

	void DestroyBuilding(UBuilding* Building);

	virtual ELoadStage GetLoadStage() override;
private:
	UPROPERTY()
	TArray<UBuilding*> Buildings;

	void Clear();

	void Init(UScenario* Scenario);
};
