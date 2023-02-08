#pragma once
#include "MyProject2/MyGameState.h"
#include "ObjectMap.generated.h"

UCLASS()
class UObjectMap : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FVector2d GetProvinceCenter(const FColor& Color);

	void CalculateProvincesCenters();

private:
	UPROPERTY()
	UTexture2D* ProvincesMapTexture;

	FVector2D SizeVector;

	TMap<FColor, FVector2d> ProvinceCenters;
};
