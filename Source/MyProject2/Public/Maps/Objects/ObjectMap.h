#pragma once
#include "Scenario.h"
#include "ObjectMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UObjectMap : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	FVector2d GetProvinceCenter(const FColor& Color);
private:
	TMap<FColor, FVector2d> ProvinceCenters;

	void CalculateProvinceCenter(const FColor& Color);

	void Clear();

	void Init(UScenario* Scenario);
};