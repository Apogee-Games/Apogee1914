#include "Economics/Instances/Buildings/MineBuilding.h"
#include "Administration/Instances/Province.h"
#include "Economics/Description/Buildings/MineDescription.h"


void UMineBuilding::Tick()
{
	// TODO: Temporary system, Think of better system that will count productivity and else
	
	if (MinResourcesCapacity != 1)
	{
		AskForResources();
	}
	
	const float ProductCount = GetPossibleProductOutputCount() * MinResourcesCapacity;
	DemandGoods(ProductCount);
	SupplyGoods(ProductCount);
}

void UMineBuilding::Init(UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince)
{
	Super::Init(ProvidedBuildingDescription, ProvidedProvince);

	for (const auto& [Resource, Amount]: GetDescription<UMineDescription>()->ResourcesRequirements)
	{
		ResourcesAcquired.Add(Resource, 0);
	}
	
	Labours = 0;
}

int32 UMineBuilding::GetLabours() const
{
	return Labours;
}

int32 UMineBuilding::GetMaxLabours() const
{
	return Cast<UMineDescription>(BuildingDescription)->MaxLabours;
}

float UMineBuilding::GetPossibleProductOutputCount()
{
	float MinProductCount = INT32_MAX;

	for (const auto& [Good, Amount] : GetDescription<UMineDescription>()->GoodsRequirements)
	{
		MinProductCount = FMath::Min(MinProductCount, GetStorage()->GetGoodAmount(Good) / Amount);
	}

	return MinProductCount == INT32_MAX ? 1 : MinProductCount; 
}

void UMineBuilding::DemandGoods(int32 ProductCount)
{
	for (const auto& [Good, Amount] : GetDescription<UMineDescription>()->GoodsRequirements)
	{
		GetStorage()->Demand(Good, Amount * ProductCount);
	}
}

void UMineBuilding::SupplyGoods(int32 ProductCount)
{
	for (const auto [Good, Amount] : GetDescription<UMineDescription>()->GoodsProduced)
	{
		GetStorage()->Supply(Good, Amount * ProductCount);
	}
}

inline UStorage* UMineBuilding::GetStorage() const
{
	return CountryController ? CountryController->GetStorage() : StrataController->GetStorage();
}

void UMineBuilding::AskForResources()
{
	MinResourcesCapacity = 1;
	
	for (const auto& [Resource, Amount]: GetDescription<UMineDescription>()->ResourcesRequirements)
	{
		if (ResourcesAcquired[Resource] == Amount) continue;
		ResourcesAcquired[Resource] += Province->GetResources()->Use(Resource, Amount);
		MinResourcesCapacity = FMath::Min(MinResourcesCapacity, ResourcesAcquired[Resource] / Amount);
	}
}
