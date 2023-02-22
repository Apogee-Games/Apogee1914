
#include "MyProject2/Economics/Instances/Public/Building.h"

void UBuilding::Produce()
{
	if(BuildingDescription == nullptr) return;
	
}

void UBuilding::Init(const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince)
{
	BuildingDescription = ProvidedBuildingDescription;	
	Labours = 0;
	Province = ProvidedProvince;
}

void UBuilding::Init(const FBuildingInstanceDescription* BuildingInstanceDescription, const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince)
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

UProvince* UBuilding::GetProvince() const
{
	return Province;
}
