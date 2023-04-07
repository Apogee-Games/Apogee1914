#include "Military/Managers/UnitsRenderer.h"

#include "Administration/Managers/ProvinceManager.h"
#include "Characters/UnitActor.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/Objects/ObjectMap.h"
#include "Military/Instances/Units/Unit.h"
#include "Military/Managers/UnitsFactory.h"
#include "Military/Managers/UnitsMover.h"

void UUnitsRenderer::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UUnitsRenderer::UnitIsMoved(UUnit* Unit, UProvince* From, UProvince* To)
{
	Actors[From]->RemoveUnit(Unit);
	Actors[To]->AddUnit(Unit);
}

void UUnitsRenderer::UnitIsCreated(UUnit* Unit)
{
	Actors[Unit->GetPosition()]->AddUnit(Unit);
}

void UUnitsRenderer::UnitIsRemoved(UUnit* Unit)
{
	Actors[Unit->GetPosition()]->RemoveUnit(Unit);
}

void UUnitsRenderer::InGameWorldInit()
{
	UGameInstance* GameInstance = GetGameInstance();
	UObjectMap* ObjectMap = GameInstance->GetSubsystem<UObjectMap>();
	
	for (const auto& Province: GameInstance->GetSubsystem<UProvinceManager>()->GetAllProvinces())
	{
		AUnitActor* Actor = GetWorld()->SpawnActor<AUnitActor>(UnitActorClass);
		const FVector2d ImagePosition = ObjectMap->GetProvinceCenter(Province->GetId());
		const FVector3d WorldPosition = GetWorldPositionFromMapPosition(ImagePosition);
		Actor->Init(WorldPosition);
		Actors.Add(Province, Actor);
	}
}

void UUnitsRenderer::Clear()
{
	UGameInstance* GameInstance = GetGameInstance();
	GameInstance->GetSubsystem<UUnitsFactory>()->RemoveUnitCreationObserver(this);
	GameInstance->GetSubsystem<UUnitsFactory>()->RemoveUnitRemovalObserver(this);
	GameInstance->GetSubsystem<UUnitsMover>()->RemoveUnitMovementObserver(this);
}

void UUnitsRenderer::Init(UScenario* Scenario)
{
	UGameInstance* GameInstance = GetGameInstance();
	GameInstance->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
	GameInstance->GetSubsystem<UUnitsFactory>()->AddUnitRemovalObserver(this);
	GameInstance->GetSubsystem<UUnitsMover>()->AddUnitMovementObserver(this);
}

FVector3d UUnitsRenderer::GetWorldPositionFromMapPosition(const FVector2d& Position)
{
	return FVector3d(0, Position.X, 1 -  Position.Y) * 200;
	// TODO: Extract all map <-> world position conversion to somewhere else
}
