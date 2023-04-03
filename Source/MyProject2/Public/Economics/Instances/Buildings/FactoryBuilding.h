#pragma once
#include "Building.h"
#include "FactoryBuilding.generated.h"

UCLASS()
class UFactoryBuilding : public UBuilding
{
	GENERATED_BODY()
public:
	virtual void Init(UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince) override;

	virtual void Tick() override;
	
	int32 GetLabours() const;

	int32 GetMaxLabours() const;
private:
	int32 Labours;

	int32 GetPossibleProductOutputCount() const;

	void DemandGoods(int32 ProductCount);

	void SupplyGoods(int32 ProductCount);

	UStorage* GetStorage() const;
};