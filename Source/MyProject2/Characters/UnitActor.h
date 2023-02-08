#pragma once
#include "Components/WidgetComponent.h"
#include "Engine/StaticMeshActor.h"
#include "MyProject2/Widgets/UnitInformationListWidget.h"
#include "UnitActor.generated.h"


class UUnit;

UCLASS()
class AUnitActor: public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AUnitActor();
	
	void Init(const FVector3d& ObjectScale, const FVector3d& Position, UStaticMesh* UnitMesh, TSubclassOf<UUnitInformationListWidget> UnitInformationListWidgetClass);

	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);

private:
	TArray<UUnit*> Units;
	
	UPROPERTY()
	UWidgetComponent* Component;

	UUnitInformationListWidget* Widget;

	void UpdateWidgetVisibility() const;
};
