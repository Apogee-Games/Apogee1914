#pragma once
#include "MyProject2/MyGameState.h"
#include "ObjectMap.generated.h"

UCLASS()
class UObjectMap : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	FVector2d GetProvinceCenter(const FColor& Color);

	void CalculateProvincesCenters();

private:
	TMap<FColor, FVector2d> ProvinceCenters;

	void CalculateProvinceCenter(const FColor& Color);
};