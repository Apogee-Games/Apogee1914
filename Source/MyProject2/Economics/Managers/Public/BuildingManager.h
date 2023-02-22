#pragma once
#include "MyProject2/Economics/Instances/Public/Building.h"
#include "BuildingManager.generated.h"

UCLASS()
class UBuildingManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	
	UBuilding* BuildBuilding(FBuildingDescription* Description, UProvince* Province);

	void Produce();

	void DestroyBuilding(UBuilding* Building);
	
private:
	
	UPROPERTY()
	TArray<UBuilding*> Buildings;

};
