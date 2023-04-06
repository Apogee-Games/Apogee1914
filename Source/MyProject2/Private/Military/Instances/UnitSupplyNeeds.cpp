#include "Military/Instances/UnitSupplyNeeds.h"

#include "Economics/Managers/GoodsManager.h"

void UUnitSupplyNeeds::Init(const TMap<FName, int32>& EquipmentRequirements)
{
	const UGoodsManager* GoodsManager = GetWorld()->GetGameInstance()->GetSubsystem<UGoodsManager>();
	
	for (const auto& [GoodName, Requirement]: EquipmentRequirements)
	{
		UGoodDescription* Good = GoodsManager->GetGoodDescription(GoodName); 
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
