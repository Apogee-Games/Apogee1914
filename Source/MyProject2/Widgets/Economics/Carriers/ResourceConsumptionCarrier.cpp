#include "ResourceConsumptionCarrier.h"

void UResourceConsumptionCarrier::Init(const FBuildingDescription* ProvidedBuildingDescription, const FName& ProvidedResourceName)
{
	BuildingDescription = ProvidedBuildingDescription;
	ResourceName = ProvidedResourceName;
}

const FName& UResourceConsumptionCarrier::GetResourceName() const
{
	return ResourceName;
}

int32 UResourceConsumptionCarrier::GetResourceConsumption() const
{
	return BuildingDescription->ResourceConsumption[ResourceName];
}
