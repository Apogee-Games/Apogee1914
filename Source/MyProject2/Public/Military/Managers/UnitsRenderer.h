#pragma once
#include "Scenario.h"
#include "Engine/StaticMeshActor.h"
#include "Characters/UnitActor.h"
#include "Military/Interfaces/Observers/UnitCreationObserver.h"
#include "Military/Interfaces/Observers/UnitMovementObserver.h"
#include "Military/Interfaces/Observers/UnitRemovalObserver.h"
#include "UnitsRenderer.generated.h"

UCLASS(Abstract, Blueprintable)
class UUnitsRenderer : public UGameInstanceSubsystem, public IUnitCreationObserver, public IUnitMovementObserver, public IUnitRemovalObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AUnitActor> UnitActorClass;

	void SetScenario(UScenario* Scenario);
	
	virtual void UnitIsMoved(UUnit* Unit, UProvince* From, UProvince* To) override;

	virtual void UnitIsCreated(UUnit* Unit) override;

	virtual void UnitIsRemoved(UUnit* Unit) override;

	void InGameWorldInit();
	
private:
	UPROPERTY()
	TMap<UProvince*, AUnitActor*> Actors;

	void Clear();

	void Init(UScenario* Scenario);
	
	static FVector3d GetWorldPositionFromMapPosition(const FVector2d& Position);
};

