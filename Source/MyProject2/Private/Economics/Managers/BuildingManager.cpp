#include "Economics/Managers//BuildingManager.h"
#include "InGameTime.h"
#include "Administration/Instances/Province.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

bool UBuildingManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UBuildingManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UBuildingManager::Tick, FTimespan(1, 0, 0, 0));
}

UBuilding* UBuildingManager::BuildBuilding(UBuildingDescription* Description, UProvince* Province)
{
	UBuilding* Building = NewObject<UBuilding>(this, Description->Class);
	Building->Init(Description, Province);

	Building->SetCountryOwner(Province->GetCountryController());
	Building->SetCountryController(Province->GetCountryController());

	Buildings.Add(Building);
	Province->AddBuilding(Building);
	return Building;
}

void UBuildingManager::Tick()
{
	for (auto& Building: Buildings)
	{
		Building->Tick();
	}
}

void UBuildingManager::DestroyBuilding(UBuilding* Building)
{
	Buildings.Remove(Building);
	Building->GetProvince()->RemoveBuilding(Building);
}
