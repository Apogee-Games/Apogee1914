#pragma once

#include "Scenario.h"
#include "Economics/Description/Goods/GoodDescription.h"
#include "Interfaces/BaseManager.h"
#include "GoodsManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UGoodsManager : public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	UGoodDescription* GetGoodDescription(const FName& GoodName) const;

	virtual ELoadStage GetLoadStage() override;
private:
	UPROPERTY()
	TMap<FName, UGoodDescription*> GoodsDescriptions;

	void Clear();

	void Init(UScenario* Scenario);
};
