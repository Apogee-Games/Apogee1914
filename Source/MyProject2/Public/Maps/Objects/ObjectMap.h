#pragma once
#include "Scenario.h"
#include "Interfaces/BaseManager.h"
#include "ObjectMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UObjectMap : public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	FVector2d GetProvinceCenter(const FColor& Color);

	virtual ELoadStage GetLoadStage() override;
private:
	TMap<FColor, FVector2d> ProvinceCenters;

	FVector2d CalculateProvinceCenter(const FColor& Color);

	void Clear();

	void Init(UScenario* Scenario);
};