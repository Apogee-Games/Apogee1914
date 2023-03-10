#include "Military/Instances/UnitSupplyNeeds.h"

void UUnitSupplyNeeds::Init(const TMap<FName, int32>& EquipmentRequirements)
{
	for (const auto& [GoodName, Requirement]: EquipmentRequirements)
	{
		Needs.Add(GoodName, Requirement);
		Requirements.Add(GoodName, Requirement);
	}
}

void UUnitSupplyNeeds::SupplyEquipment(const FName& GoodName, int32 Amount)
{
	Needs[GoodName] -= Amount;
}

int32 UUnitSupplyNeeds::DemandEquipment(const FName& GoodName, int32 Amount)
{
	const int32 PossibleAmount = FMath::Min(GetGoodSupply(GoodName), Amount);
	Needs[GoodName] += PossibleAmount;
	return PossibleAmount;
}

int32 UUnitSupplyNeeds::GetGoodSupply(const FName& GoodName) const
{
	return Requirements[GoodName] - Needs[GoodName];
}

int32 UUnitSupplyNeeds::GetGoodRequirements(const FName& GoodName) const
{
	return Requirements[GoodName];
}

const TMap<FName, int32>& UUnitSupplyNeeds::GetNeeds() const
{
	return Needs;
}

const TMap<FName, int32>& UUnitSupplyNeeds::GetRequirements() const
{
	return Requirements;
}
