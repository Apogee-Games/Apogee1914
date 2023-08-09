#pragma once
#include "Economics/Instances/Buildings/Building.h"
#include "Interfaces/BaseManager.h"
#include "BuildingManager.generated.h"

UENUM()
enum class EBuildingStatus
{
	StartedConstruction,
	Constructed,
	StartedDestruction,
	Destroyed
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBuildingStatusChanged, UBuilding*, EBuildingStatus)

UCLASS(Abstract, Blueprintable)
class UBuildingManager: public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;

	void Tick();

	UBuilding* BuildBuilding(UBuildingDescription* Description, UProvince* Province);
	void DestroyBuilding(UBuilding* Building);

	virtual ELoadStage GetLoadStage() override;

	FOnBuildingStatusChanged OnBuildingStatusChanged;

	const TArray<UBuilding*>& GetBuildings() const { return Buildings; }
private:
	UPROPERTY()
	TArray<UBuilding*> Buildings;

	void Clear();

	void Init(UScenario* Scenario);
};
