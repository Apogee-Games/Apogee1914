#include "UnitsRenderer.h"

#include "UnitsFactory.h"
#include "UnitsMover.h"
#include "MyProject2/MyProject2GameModeBase.h"
#include "MyProject2/Widgets/Military/Units/UnitInformationListWidget.h"
#include "MyProject2/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Characters/UnitActor.h"
#include "MyProject2/Maps/Objects/ObjectMap.h"
#include "MyProject2/Maps/Precalculations/ProvincesMap.h"
#include "MyProject2/Military/Instances/Units/Unit.h"

void UUnitsRenderer::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitRemovalObserver(this);
	GetWorld()->GetSubsystem<UUnitsMover>()->AddUnitMovementObserver(this);
}

void UUnitsRenderer::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UProvincesMap>()->RegisterOnFullInitializationAction(this, &UUnitsRenderer::Init);
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

void UUnitsRenderer::Init()
{
	const TSubclassOf<UUnitInformationListWidget> UnitInformationListWidgetClass = GetWorld()->GetGameState<AMyGameState>()->UnitInformationListWidgetClass;
	for (const auto& Province: GetWorld()->GetSubsystem<UProvinceManager>()->GetAllProvinces())
	{
		AUnitActor* Actor = GetWorld()->SpawnActor<AUnitActor>(AUnitActor::StaticClass());
		const FVector2d ImagePosition = GetWorld()->GetSubsystem<UObjectMap>()->GetProvinceCenter(Province->GetId());
		const FVector3d WorldPosition = GetWorldPositionFromMapPosition(ImagePosition);
		Actor->Init(ObjectScale, WorldPosition, UnitMesh, UnitInformationListWidgetClass);
		Actors.Add(Province, Actor);
	}
}

FVector3d UUnitsRenderer::GetWorldPositionFromMapPosition(const FVector2d& Position)
{
	return FVector3d(0, Position.X, 1 -  Position.Y) * 200;
	// TODO: Extract all map <-> world position conversion to somewhere else
}
