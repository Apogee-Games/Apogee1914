#pragma once
#include "Components/WidgetComponent.h"
#include "Engine/StaticMeshActor.h"
#include "UnitActor.generated.h"

class UUnitInformationListWidget;
class FUnit;

UCLASS()
class AUnitActor: public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AUnitActor();
	
	void Init(const FVector3d& ObjectScale, const FVector3d& Position, UStaticMesh* UnitMesh, const TSubclassOf<UUnitInformationListWidget>& UnitInformationListWidgetClass);

	void AddUnit(FUnit* Unit);

	void RemoveUnit(FUnit* Unit);

private:
	TArray<FUnit*> Units;
	
	UPROPERTY()
	UWidgetComponent* Component;

	UUnitInformationListWidget* Widget;

	void UpdateWidgetVisibility() const;
};
