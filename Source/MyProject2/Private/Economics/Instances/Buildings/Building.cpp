#include "Economics/Instances/Buildings/Building.h"

#include "Economics/Managers/BuildingManager.h"

void UBuilding::Init(UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince)
{
	BuildingDescription = ProvidedBuildingDescription;	
	Province = ProvidedProvince;

	FOnBuildingStatusChanged& OnBuildingStatusChanged = Cast<UBuildingManager>(GetOuter())->OnBuildingStatusChanged;
	if (OnBuildingStatusChanged.IsBound())
	{
		OnBuildingStatusChanged.Broadcast(this, EBuildingStatus::Constructed);
	}
}

void UBuilding::Destroy()
{
	FOnBuildingStatusChanged& OnBuildingStatusChanged = Cast<UBuildingManager>(GetOuter())->OnBuildingStatusChanged;
	if (OnBuildingStatusChanged.IsBound())
	{
		OnBuildingStatusChanged.Broadcast(this, EBuildingStatus::Destroyed);
	}
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
