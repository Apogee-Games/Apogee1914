#pragma once
#include "GoodsSubgroup.h"
#include "GoodsGroup.generated.h"

UCLASS()
class UGoodsGroup : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText GroupName;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UGoodsSubgroup*> Subgroups;
};