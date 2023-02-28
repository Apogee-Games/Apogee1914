#pragma once
#include "MyProject2/Military/Instances/Units/Unit.h"
#include "Engine/StaticMeshActor.h"
#include "MyProject2/Characters/UnitActor.h"
#include "MyProject2/Military/Interfaces/Observers/UnitCreationObserver.h"
#include "MyProject2/Military/Interfaces/Observers/UnitMovementObserver.h"
#include "MyProject2/Military/Interfaces/Observers/UnitRemovalObserver.h"
#include "MyProject2/Widgets/Military/Units/UnitInformationListWidget.h"
#include "UnitsRenderer.generated.h"

UCLASS()
class UUnitsRenderer : public UWorldSubsystem, public IUnitCreationObserver, public IUnitMovementObserver, public IUnitRemovalObserver
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void UnitIsMoved(FUnit* Unit, UProvince* From, UProvince* To) override;

	virtual void UnitIsCreated(FUnit* Unit) override;

	virtual void UnitIsRemoved(FUnit* Unit) override;

	void Init();
	
private:
	UPROPERTY()
	TMap<UProvince*, AUnitActor*> Actors;
	
	UPROPERTY()
	UStaticMesh* UnitMesh = FindObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	FVector3d ObjectScale = FVector3d(0.01, 0.005, 0.005);
	
	static FVector3d GetWorldPositionFromMapPosition(const FVector2d& Position);
};

