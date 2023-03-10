#pragma once
#include "UnitSupplyNeeds.generated.h"

UCLASS()
class UUnitSupplyNeeds: public UObject
{
	GENERATED_BODY()
public:
	void Init(const TMap<FName, int32> &EquipmentRequirements);

	void SupplyEquipment(const FName& GoodName, int32 Amount);

	int32 DemandEquipment(const FName& GoodName, int32 Amount);

	int32 GetGoodSupply(const FName& GoodName) const;

	int32 GetGoodRequirements(const FName& GoodName) const;

	const TMap<FName, int32>& GetNeeds() const;

	const TMap<FName, int32>& GetRequirements() const;
	
private:
	TMap<FName, int32> Needs;
	
	TMap<FName, int32> Requirements;
};
