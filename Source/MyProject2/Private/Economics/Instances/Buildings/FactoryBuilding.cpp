#include "Economics/Instances/Buildings/FactoryBuilding.h"
#include "Economics/Description/Buildings/FactoryDescription.h"


void UFactoryBuilding::Tick()
{
	// TODO: Temporary system, Think of better system that will count productivity and else
	const int32 ProductCount = GetPossibleProductOutputCount();
	DemandGoods(ProductCount);
	SupplyGoods(ProductCount);
}

void UFactoryBuilding::Init(UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince)
{
	Super::Init(ProvidedBuildingDescription, ProvidedProvince);
	Labours = 0;
}

int32 UFactoryBuilding::GetLabours() const
{
	return Labours;
}

int32 UFactoryBuilding::GetMaxLabours() const
{
	return Cast<UFactoryDescription>(BuildingDescription)->MaxLabours;
}

int32 UFactoryBuilding::GetPossibleProductOutputCount() const
{
	int32 MinProductCount = INT32_MAX;
	
	/*for (const auto [Good, Amount] : BuildingDescription->GoodConsumption)
	{
		MinProductCount = FMath::Min(MinProductCount, GetStorage()->GetGoodAmount(Good) / Amount);
	}*/

	return MinProductCount == INT32_MAX ? 1 : MinProductCount; 
}

void UFactoryBuilding::DemandGoods(int32 ProductCount)
{
	/*for (const auto [Good, Amount] : BuildingDescription->GoodConsumption)
	{
		GetStorage()->Demand(Good, Amount * ProductCount);
	}*/
}

void UFactoryBuilding::SupplyGoods(int32 ProductCount)
{
	/*for (const auto [Good, Amount] : BuildingDescription->GoodOutput)
	{
		GetStorage()->Supply(Good, Amount * ProductCount);
	}*/
}

inline UStorage* UFactoryBuilding::GetStorage() const
{
	return CountryController ? CountryController->GetStorage() : StrataController->GetStorage();
}
