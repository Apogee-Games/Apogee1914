
#include "MyProject2/Economics/Instances/Public/Building.h"

void UBuilding::Produce()
{
	// TODO: Temporary system, Think of better system that will count productivity and else
	const int32 ProductCount = GetPossibleProductOutputCount();
	DemandGoods(ProductCount);
	SupplyGoods(ProductCount);
}

void UBuilding::Init(const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince, UStorage* ProvidedStorage)
{
	BuildingDescription = ProvidedBuildingDescription;	
	Labours = 0;
	Province = ProvidedProvince;
	Storage = ProvidedStorage;
}

void UBuilding::Init(const FBuildingInstanceDescription* BuildingInstanceDescription, const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince, UStorage* ProvidedStorage)
{
	BuildingDescription = ProvidedBuildingDescription;	
	Labours = BuildingInstanceDescription->Labours;
	Province = ProvidedProvince;
	Storage = ProvidedStorage;
}

const FBuildingDescription* UBuilding::GetBuildingDescription() const
{
	return BuildingDescription;
}

int32 UBuilding::GetLabours() const
{
	return Labours;
}

UProvince* UBuilding::GetProvince() const
{
	return Province;
}

int UBuilding::GetPossibleProductOutputCount() const
{
	int32 MinProductCount = INT32_MAX;
	
	for (const auto [Good, Amount] : BuildingDescription->GoodConsumption)
	{
		MinProductCount = FMath::Min(MinProductCount, Storage->GetGoodAmount(Good) / Amount);
	}

	return MinProductCount == INT32_MAX ? 1 : MinProductCount; 
}

void UBuilding::DemandGoods(int ProductCount)
{
	for (const auto [Good, Amount] : BuildingDescription->GoodConsumption)
	{
		Storage->Demand(Good, Amount * ProductCount);
	}
}

void UBuilding::SupplyGoods(int ProductCount)
{
	for (const auto [Good, Amount] : BuildingDescription->GoodOutput)
	{
		Storage->Supply(Good, Amount * ProductCount);
	}
} 