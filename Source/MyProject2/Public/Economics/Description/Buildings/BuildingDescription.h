#pragma once
#include "Engine/DataTable.h"
#include "BuildingDescription.generated.h"

class UBuilding;

UCLASS()
class UBuildingDescription : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	FName Type;
	
	UPROPERTY(EditDefaultsOnly)
	FName Group;

	UPROPERTY(EditDefaultsOnly)
	FName Subgroup;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBuilding> Class;
};