#pragma once
#include "Engine/StaticMeshActor.h"
#include "MyProject2/Characters/UnitActor.h"
#include "MyProject2/Military/Interfaces/Observers/UnitCreationObserver.h"
#include "MyProject2/Military/Interfaces/Observers/UnitMovementObserver.h"
#include "MyProject2/Military/Interfaces/Observers/UnitRemovalObserver.h"
#include "MyProject2/Widgets/UnitInformationListWidget.h"
#include "UnitsRenderer.generated.h"

UCLASS()
class UUnitsRenderer : public UWorldSubsystem, public IUnitCreationObserver, public IUnitMovementObserver, public IUnitRemovalObserver
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void UnitIsMoved(UUnit* Unit, const FColor& From, const FColor& To) override;

	virtual void UnitIsCreated(UUnit* Unit) override;

	virtual void UnitIsRemoved(UUnit* Unit) override;

	void BeginPlay();
	
	void SetUnitInformationWidgetClass(TSubclassOf<UUnitInformationListWidget> NewUnitInformationListWidgetClass);
	
private:
	UPROPERTY()
	TMap<FColor, AUnitActor*> Actors;
	
	TSubclassOf<UUnitInformationListWidget> UnitInformationListWidgetClass;

	UPROPERTY()
	UStaticMesh* UnitMesh = FindObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	FVector3d ObjectScale = FVector3d(0.01, 0.005, 0.005);
	
	static FVector3d GetWorldPositionFromMapPosition(const FVector2d& Position);
};
