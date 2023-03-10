

#include "Economics/Managers//BuildingManager.h"

#include "InGameTime.h"
#include "Administration/Instances/Province.h"

void UBuildingManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UBuildingManager::Produce, FTimespan(1, 0, 0, 0));
}

UBuilding* UBuildingManager::BuildBuilding(const FBuildingDescription* Description, UProvince* Province, UStorage* Storage)
{
	UBuilding* Building = NewObject<UBuilding>();
	Building->Init(Description, Province, Storage);
	Buildings.Add(Building);
	Province->AddBuilding(Building);
	return Building;
}

void UBuildingManager::Produce()
{
	for (auto& Building: Buildings)
	{
		Building->Produce();
	}
}

void UBuildingManager::DestroyBuilding(UBuilding* Building)
{
	Buildings.Remove(Building);
	Building->GetProvince()->RemoveBuilding(Building);
}
