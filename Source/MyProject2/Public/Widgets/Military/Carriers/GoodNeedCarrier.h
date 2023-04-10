#pragma once
#include "Military/Instances/UnitSupplyNeeds.h"

#include "GoodNeedCarrier.generated.h"

UCLASS()
class UGoodNeedCarrier: public UObject
{
	GENERATED_BODY()
public:
	void Init(UUnitSupplyNeeds* ProvidedUnitSupplyNeed, UGoodDescription* ProvidedGoodName);

	float GetGoodSupply() const;

	float GetGoodRequirements() const;

	const FText& GetGoodName() const;
private:
	UPROPERTY()
	UUnitSupplyNeeds* UnitSupplyNeeds;

	UPROPERTY()
	UGoodDescription* Good;
};
