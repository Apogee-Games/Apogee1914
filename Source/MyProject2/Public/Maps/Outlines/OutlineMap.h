#pragma once
#include "OutlineMap.generated.h"

UCLASS()
class UOutlineMap: public UWorldSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	void CreateOutline();

private:
	UPROPERTY()
	UTexture2D* OutlinesMapTexture;
	
	FVector2D SizeVector;

	FColor OutlineColor = FColor(0, 0, 0);
	
	FColor BackgroundColor = FColor(255, 255, 255);
};
