#pragma once
#include "Scenario.h"
#include "Interfaces/BaseManager.h"

#include "IdeologiesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UIdeologiesMap: public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;

	void UpdateMap();

	virtual ELoadStage GetLoadStage() override;
private:
	UPROPERTY()
	UTexture2D* IdeologiesMapTexture;
	
	void Clear();

	void Init(UScenario* Scenario);
};
