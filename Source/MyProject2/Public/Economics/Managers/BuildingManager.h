#pragma once
#include "Economics/Instances/Buildings/Building.h"
#include "BuildingManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UBuildingManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	UBuilding* BuildBuilding(UBuildingDescription* Description, UProvince* Province);

	void Tick();

	void DestroyBuilding(UBuilding* Building);
private:
	UPROPERTY()
	TArray<UBuilding*> Buildings;
};
