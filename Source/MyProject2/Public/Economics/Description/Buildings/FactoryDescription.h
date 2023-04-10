#pragma once
#include "BuildingDescription.h"
#include "Economics/Description/Goods/GoodsGroup.h"
#include "FactoryDescription.generated.h"

USTRUCT()
struct FProducibleGoods
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<UGoodsGroup*> GoodsGroups;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UGoodsSubgroup*> GoodsSubgroups;

	UPROPERTY(EditDefaultsOnly)
	TArray<UGoodDescription*> Goods;
}; 

UCLASS()
class UFactoryDescription: public UBuildingDescription
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FProducibleGoods ProducibleGoods;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MaxLabours = 0;

	UPROPERTY(EditDefaultsOnly)
	float OutputCost;
};
