#pragma once
#include "MyProject2/MyGameState.h"
#include "ObjectMap.generated.h"

UCLASS()
class UObjectMap : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	TMap<FColor, int> CalculateProvincesCenters() const;
private:
	UPROPERTY()
	UTexture2D* ProvincesMapTexture;

	FVector2D SizeVector;
};
