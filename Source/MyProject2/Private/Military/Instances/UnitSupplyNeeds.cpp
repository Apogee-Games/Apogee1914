#include "Military/Instances/UnitSupplyNeeds.h"

#include "Economics/Managers/GoodsManager.h"

void UUnitSupplyNeeds::Init(const TMap<UGoodDescription*, int32>& EquipmentRequirements)
{
	for (const auto& [Good, Requirement]: EquipmentRequirements)
	{
		Needs.Add(Good, Requirement);
		Requirements.Add(Good, Requirement);
	}
}

void UUnitSupplyNeeds::SupplyEquipment(UGoodDescription* Good, int32 Amount)
{
	Needs[Good] -= Amount;
}

int32 UUnitSupplyNeeds::DemandEquipment(UGoodDescription* Good, int32 Amount)
{
	const int32 PossibleAmount = FMath::Min(GetGoodSupply(Good), Amount);
	Needs[Good] += PossibleAmount;
	return PossibleAmount;
}

int32 UUnitSupplyNeeds::GetGoodSupply(UGoodDescription* Good) const
{
	return Requirements[Good] - Needs[Good];
}

int32 UUnitSupplyNeeds::GetGoodRequirements(UGoodDescription* Good) const
{
	return Requirements[Good];
}

const TMap<UGoodDescription*, int32>& UUnitSupplyNeeds::GetNeeds() const
{
	return Needs;
}

const TMap<UGoodDescription*, int32>& UUnitSupplyNeeds::GetRequirements() const
{
	return Requirements;
}

float UUnitSupplyNeeds::GetSupplyPercentage()
{
	float SupplyPercentage = 1.0;

	for (const auto& [Good, Required]: Requirements)
	{
		SupplyPercentage *= (Required - Needs[Good]) / Required;
	}

	return SupplyPercentage;
}
