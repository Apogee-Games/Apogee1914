#pragma once
#include "BuildingDescription.h"
#include "FactoryDescription.generated.h"

USTRUCT()
struct FProducibleGoods
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName Group;
	
	UPROPERTY(EditDefaultsOnly)
	FName Subgroup;
};

UCLASS()
class UFactoryDescription: public UBuildingDescription
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FProducibleGoods> ProducibleGoodsGroup;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MaxLabours = 0;
};
