#pragma once
#include "MyProject2/Military/Instances/UnitSupplyNeeds.h"

#include "GoodNeedCarrier.generated.h"

UCLASS()
class UGoodNeedCarrier: public UObject
{
	GENERATED_BODY()
public:
	void Init(UUnitSupplyNeeds* ProvidedUnitSupplyNeed, const FName& ProvidedGoodName);

	int32 GetGoodSupply() const;

	int32 GetGoodRequirements() const;

	const FName& GetGoodName() const;
	
private:
	UPROPERTY()
	UUnitSupplyNeeds* UnitSupplyNeeds;

	FName GoodName;
};
