#pragma once
#include "Economics/Description/Goods/GoodDescription.h"
#include "UnitSupplyNeeds.generated.h"

UCLASS()
class UUnitSupplyNeeds: public UObject
{
	GENERATED_BODY()
public:
	void Init(const TMap<FName, int32> &EquipmentRequirements);

	void SupplyEquipment(UGoodDescription* Good, int32 Amount);

	int32 DemandEquipment(UGoodDescription* Good, int32 Amount);

	int32 GetGoodSupply(UGoodDescription* Good) const;

	int32 GetGoodRequirements(UGoodDescription* Good) const;

	const TMap<UGoodDescription*, int32>& GetNeeds() const;

	const TMap<UGoodDescription*, int32>& GetRequirements() const;
private:
	UPROPERTY()
	TMap<UGoodDescription*, int32> Needs;
	
	UPROPERTY()
	TMap<UGoodDescription*, int32> Requirements;
};
