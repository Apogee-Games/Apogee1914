#pragma once
#include "GoodDescription.h"
#include "GoodsSubgroup.generated.h"

UCLASS()
class UGoodsSubgroup : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText SubgroupName;

	UPROPERTY(EditDefaultsOnly)
	TArray<UGoodDescription*> Goods;
};