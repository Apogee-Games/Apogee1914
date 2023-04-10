#pragma once
#include "Building.h"
#include "Economics/Description/Goods/CookedGoodDescription.h"
#include "Economics/Instances/Storage.h"
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

	void SetGoodToProduce(UCookedGoodDescription* ProvidedGoodToProduce);

	UCookedGoodDescription* GetGoodToProduce() const;
private:
	UPROPERTY()
	UCookedGoodDescription* GoodToProduce;
	
	int32 Labours;

	float GetPossibleProductOutputCount() const;

	void DemandGoods(float ProductCount);

	void SupplyGoods(int32 ProductCount);

	UStorage* GetStorage() const;
};