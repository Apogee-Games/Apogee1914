#pragma once
#include "Engine/DataTable.h"
#include "TerrainDescription.generated.h"

UCLASS()
class UTerrainDescription : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	
	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed = 1;
};
