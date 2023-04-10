#include "Economics/Instances/Buildings/FactoryBuilding.h"

#include "Administration/Instances/Country.h"
#include "Economics/Description/Buildings/FactoryDescription.h"


void UFactoryBuilding::Tick()
{
	// TODO: Temporary system, Think of better system that will count productivity and else
	if (!GoodToProduce) return;
	const float ProductCount = GetPossibleProductOutputCount();
	DemandGoods(ProductCount);
	SupplyGoods(ProductCount);
}

void UFactoryBuilding::Init(UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince)
{
	Super::Init(ProvidedBuildingDescription, ProvidedProvince);
	Labours = GetDescription<UFactoryDescription>()->MaxLabours;
}

int32 UFactoryBuilding::GetLabours() const
{
	return Labours;
}

int32 UFactoryBuilding::GetMaxLabours() const
{
	return Cast<UFactoryDescription>(BuildingDescription)->MaxLabours;
}

void UFactoryBuilding::SetGoodToProduce(UCookedGoodDescription* ProvidedGoodToProduce)
{
	GoodToProduce = ProvidedGoodToProduce;	
}

UCookedGoodDescription* UFactoryBuilding::GetGoodToProduce() const
{
	return GoodToProduce;
}

float UFactoryBuilding::GetPossibleProductOutputCount() const
{
	const float BaseOutput = GetDescription<UFactoryDescription>()->OutputCost / GoodToProduce->Cost;

	float MinGoodsCapacity = 1;
	
	for (const auto& [Good, Amount] : GoodToProduce->GoodsRequirements)
	{
		const float Needed = Amount * BaseOutput;
		const float Possible = GetStorage()->Estimate(Good, Amount * BaseOutput);
		MinGoodsCapacity = FMath::Min(MinGoodsCapacity, Possible / Needed);
	}
	
	const float LabourCapacity = Labours / GetDescription<UFactoryDescription>()->MaxLabours;
	
	return BaseOutput * MinGoodsCapacity * LabourCapacity; 
}

void UFactoryBuilding::DemandGoods(float ProductCount)
{
	for (const auto& [Good, Amount] : GoodToProduce->GoodsRequirements)
	{
		GetStorage()->Demand(Good, Amount * ProductCount);
	}
}	

void UFactoryBuilding::SupplyGoods(int32 ProductCount)
{
	GetStorage()->Supply(GoodToProduce, ProductCount);
}

inline UStorage* UFactoryBuilding::GetStorage() const
{
	return CountryController ? CountryController->GetStorage() : StrataController->GetStorage();
}
