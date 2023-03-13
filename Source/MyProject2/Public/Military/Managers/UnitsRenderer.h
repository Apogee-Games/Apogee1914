#pragma once
#include "Engine/StaticMeshActor.h"
#include "Characters/UnitActor.h"
#include "Military/Interfaces/Observers/UnitCreationObserver.h"
#include "Military/Interfaces/Observers/UnitMovementObserver.h"
#include "Military/Interfaces/Observers/UnitRemovalObserver.h"
#include "UnitsRenderer.generated.h"

UCLASS(Abstract, Blueprintable)
class UUnitsRenderer : public UWorldSubsystem, public IUnitCreationObserver, public IUnitMovementObserver, public IUnitRemovalObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AUnitActor> UnitActorClass;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void UnitIsMoved(UUnit* Unit, UProvince* From, UProvince* To) override;

	virtual void UnitIsCreated(UUnit* Unit) override;

	virtual void UnitIsRemoved(UUnit* Unit) override;

	void Init();
	
private:
	UPROPERTY()
	TMap<UProvince*, AUnitActor*> Actors;
	
	static FVector3d GetWorldPositionFromMapPosition(const FVector2d& Position);
};

