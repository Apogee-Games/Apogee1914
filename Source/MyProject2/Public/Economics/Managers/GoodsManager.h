#pragma once

#include "Economics/Description/Goods/GoodDescription.h"
#include "GoodsManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UGoodsManager : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	UGoodDescription* GetGoodDescription(const FName& GoodName) const;
private:
	UPROPERTY()
	TMap<FName, UGoodDescription*> GoodsDescriptions;
};
