#include "Economics/Instances/Buildings/Building.h"

void UBuilding::Init(UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince)
{
	BuildingDescription = ProvidedBuildingDescription;	
	Province = ProvidedProvince;
}

UBuildingDescription* UBuilding::GetDescription() const
{
	return BuildingDescription;
}

void UBuilding::Tick()
{
}

UProvince* UBuilding::GetProvince() const
{
	return Province;
}

const FText& UBuilding::GetName() const
{
	return BuildingDescription->Name;
}
