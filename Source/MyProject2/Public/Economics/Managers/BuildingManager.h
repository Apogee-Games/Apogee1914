#pragma once
#include "Scenario.h"
#include "Economics/Instances/Buildings/Building.h"
#include "Economics/Interfaces/Observables/BuildingCreationObservable.h"
#include "BuildingManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UBuildingManager: public UGameInstanceSubsystem, public IBuildingCreationObservable
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	UBuilding* BuildBuilding(UBuildingDescription* Description, UProvince* Province);

	void Tick();

	void DestroyBuilding(UBuilding* Building);
private:
	UPROPERTY()
	TArray<UBuilding*> Buildings;

	void Clear();

	void Init(UScenario* Scenario);
};
