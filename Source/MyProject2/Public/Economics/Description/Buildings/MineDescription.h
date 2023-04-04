#pragma once
#include "BuildingDescription.h"
#include "MineDescription.generated.h"

UCLASS()
class UMineDescription: public UBuildingDescription
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TMap<UResourceDescription*, float> ResourcesRequirements;

	UPROPERTY(EditDefaultsOnly)
	TMap<UGoodDescription*, float> GoodsRequirements;

	UPROPERTY(EditDefaultsOnly)
	TMap<UGoodDescription*, float> GoodsProduced;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MaxLabours = 0;
};
