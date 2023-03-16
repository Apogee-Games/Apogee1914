#pragma once
#include "ObjectMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UObjectMap : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	FVector2d GetProvinceCenter(const FColor& Color);

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void CalculateProvincesCenters();
private:
	TMap<FColor, FVector2d> ProvinceCenters;

	void CalculateProvinceCenter(const FColor& Color);
};