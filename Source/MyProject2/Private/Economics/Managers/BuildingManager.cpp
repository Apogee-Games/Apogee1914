#include "Economics/Managers//BuildingManager.h"
#include "InGameTime.h"
#include "Administration/Instances/Province.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

void UBuildingManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
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
	Building->Destroy();
	Buildings.Remove(Building);
	Building->GetProvince()->RemoveBuilding(Building);
}

ELoadStage UBuildingManager::GetLoadStage()
{
	return ELoadStage::BuildingManager;
}

void UBuildingManager::Clear()
{
	Buildings.Empty();
}

void UBuildingManager::Init(UScenario* Scenario)
{
	// TODO: Add descriptions
	GetGameInstance()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UBuildingManager::Tick, FTimespan(1, 0, 0, 0));
}
