#include "BuildingDescriptionCarrier.h"

void UBuildingDescriptionCarrier::Init(const FBuildingDescription* ProvidedBuildingDescription)
{
	BuildingDescription = ProvidedBuildingDescription;
}

const FBuildingDescription* UBuildingDescriptionCarrier::GetBuildingDescription() const
{
	return BuildingDescription;
}
