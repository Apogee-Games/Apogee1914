#pragma once
#include "Engine/StaticMeshActor.h"
#include "UnitsRenderer.generated.h"

class UUnitInformationListWidget;
class AUnitActor;
class UUnit;

UCLASS()
class UUnitsRenderer : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void UnitIsMoved(UUnit* Unit, const FColor& From, const FColor& To);

	virtual void UnitIsCreated(UUnit* Unit);

	virtual void UnitIsRemoved(UUnit* Unit);

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

