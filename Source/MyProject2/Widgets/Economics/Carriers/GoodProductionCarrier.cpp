#include "GoodProductionCarrier.h"

void UGoodProductionCarrier::Init(const FBuildingDescription* ProvidedBuildingDescription, const FName& ProvidedGoodName)
{
	BuildingDescription = ProvidedBuildingDescription;
	GoodName = ProvidedGoodName;
}

const FName& UGoodProductionCarrier::GetGoodName() const
{
	return GoodName;
}

int32 UGoodProductionCarrier::GetGoodProduction() const
{
	return BuildingDescription->GoodOutput[GoodName];
}
