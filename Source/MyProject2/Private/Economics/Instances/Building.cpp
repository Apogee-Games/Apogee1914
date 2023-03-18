

#include "Economics/Instances/Building.h"

void UBuilding::Produce()
{
	// TODO: Temporary system, Think of better system that will count productivity and else
	const int32 ProductCount = GetPossibleProductOutputCount();
	DemandGoods(ProductCount);
	SupplyGoods(ProductCount);
}

void UBuilding::Init(const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince)
{
	BuildingDescription = ProvidedBuildingDescription;	
	Labours = 0;
	Province = ProvidedProvince;
}

void UBuilding::Init(const FBuildingInstanceDescription* BuildingInstanceDescription, const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince, UStorage* ProvidedStorage)
{
	BuildingDescription = ProvidedBuildingDescription;	
	Labours = BuildingInstanceDescription->Labours;
	Province = ProvidedProvince;
}

const FBuildingDescription* UBuilding::GetBuildingDescription() const
{
	return BuildingDescription;
}

int32 UBuilding::GetLabours() const
{
	return Labours;
}

int32 UBuilding::GetMaxLabours() const
{
	return BuildingDescription->MaxLabours;
}

UProvince* UBuilding::GetProvince() const
{
	return Province;
}

const FName& UBuilding::GetBuildingName() const
{
	return BuildingDescription->BuildingName;
}

int32 UBuilding::GetPossibleProductOutputCount() const
{
	int32 MinProductCount = INT32_MAX;
	
	for (const auto [Good, Amount] : BuildingDescription->GoodConsumption)
	{
		MinProductCount = FMath::Min(MinProductCount, GetStorage()->GetGoodAmount(Good) / Amount);
	}

	return MinProductCount == INT32_MAX ? 1 : MinProductCount; 
}

void UBuilding::DemandGoods(int32 ProductCount)
{
	for (const auto [Good, Amount] : BuildingDescription->GoodConsumption)
	{
		GetStorage()->Demand(Good, Amount * ProductCount);
	}
}

void UBuilding::SupplyGoods(int32 ProductCount)
{
	for (const auto [Good, Amount] : BuildingDescription->GoodOutput)
	{
		GetStorage()->Supply(Good, Amount * ProductCount);
	}
}

inline UStorage* UBuilding::GetStorage() const
{
	return CountryController ? CountryController->GetStorage() : StrataController->GetStorage();
} 