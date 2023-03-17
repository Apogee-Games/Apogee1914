#include "Military/Managers/UnitsRenderer.h"

#include "Administration/Managers/ProvinceManager.h"
#include "Characters/UnitActor.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/Objects/ObjectMap.h"
#include "Military/Instances/Units/Unit.h"
#include "Military/Managers/UnitsFactory.h"
#include "Military/Managers/UnitsMover.h"

bool UUnitsRenderer::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UUnitsRenderer::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitRemovalObserver(this);
	GetWorld()->GetSubsystem<UUnitsMover>()->AddUnitMovementObserver(this);

	UObjectMap* ObjectMap = GetWorld()->GetGameInstance()->GetSubsystem<UObjectMap>();
	
	for (const auto& Province: GetWorld()->GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces())
	{
		AUnitActor* Actor = GetWorld()->SpawnActor<AUnitActor>(UnitActorClass);
		const FVector2d ImagePosition = ObjectMap->GetProvinceCenter(Province->GetId());
		const FVector3d WorldPosition = GetWorldPositionFromMapPosition(ImagePosition);
		Actor->Init(WorldPosition);
		Actors.Add(Province, Actor);
	}
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

FVector3d UUnitsRenderer::GetWorldPositionFromMapPosition(const FVector2d& Position)
{
	return FVector3d(0, Position.X, 1 -  Position.Y) * 200;
	// TODO: Extract all map <-> world position conversion to somewhere else
}
