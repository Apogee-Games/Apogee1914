#pragma once
#include "Building.h"
#include "Economics/Description/ResourceDescription.h"
#include "Economics/Instances/Storage.h"
#include "MineBuilding.generated.h"

UCLASS()
class UMineBuilding: public UBuilding
{
	GENERATED_BODY()
public:
	virtual void Init(UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince) override;

	virtual void Tick() override;
	
	int32 GetLabours() const;

	int32 GetMaxLabours() const;
private:
	int32 Labours;

	float MinResourcesCapacity = 0.0;

	UPROPERTY()
	TMap<UResourceDescription*, float> ResourcesAcquired;

	float GetPossibleProductOutputCount();

	void DemandGoods(int32 ProductCount);

	void SupplyGoods(int32 ProductCount);

	UStorage* GetStorage() const;

	void AskForResources();
};
