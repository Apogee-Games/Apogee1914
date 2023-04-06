#pragma once

#include "Scenario.h"
#include "Economics/Description/Goods/GoodDescription.h"
#include "GoodsManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UGoodsManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	UGoodDescription* GetGoodDescription(const FName& GoodName) const;
private:
	UPROPERTY()
	TMap<FName, UGoodDescription*> GoodsDescriptions;

	void Clear();

	void Init(UScenario* Scenario);
};
