
#include "Widgets/Economics/Buildings/Carriers/GoodConsumptionCarrier.h"

void UGoodConsumptionCarrier::Init(const FBuildingDescription* ProvidedBuildingDescription, const FName& ProvidedGoodName)
{
	BuildingDescription = ProvidedBuildingDescription;
	GoodName = ProvidedGoodName;
}

const FName& UGoodConsumptionCarrier::GetGoodName() const
{
	return GoodName;
}

int32 UGoodConsumptionCarrier::GetGoodConsumption() const
{
	return BuildingDescription->GoodConsumption[GoodName];
}
