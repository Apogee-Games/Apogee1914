#pragma once
#include "MyProject2/Economics/Instances/Public/Building.h"
#include "MyProject2/Economics/Instances/Public/Storage.h"
#include "BuildingManager.generated.h"

UCLASS()
class UBuildingManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	UBuilding* BuildBuilding(const FBuildingDescription* Description, UProvince* Province, UStorage* Storage);

	void Produce();

	void DestroyBuilding(UBuilding* Building);
	
private:
	
	UPROPERTY()
	TArray<UBuilding*> Buildings;

};
