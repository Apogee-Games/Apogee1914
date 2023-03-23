#pragma once
#include "Economics/Instances/Building.h"
#include "Economics/Instances/Storage.h"
#include "BuildingManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UBuildingManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	UBuilding* BuildBuilding(const FBuildingDescription* Description, UProvince* Province);

	void Produce();

	void DestroyBuilding(UBuilding* Building);
private:
	UPROPERTY()
	TArray<UBuilding*> Buildings;
};
