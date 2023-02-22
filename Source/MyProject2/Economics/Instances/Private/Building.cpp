
#include "MyProject2/Economics/Instances/Public/Building.h"

void UBuilding::Produce()
{
	if(BuildingDescription == nullptr) return;
	for (const auto [Good, Amount] : BuildingDescription->GoodOutput)
	{
		Storage->Supply(Good, Amount);
	}
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
