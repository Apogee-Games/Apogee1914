#pragma once
#include "MyProject2/MyGameState.h"
#include "OutlineMap.generated.h"

UCLASS()
class UOutlineMap: public UWorldSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void CreateOutline();

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	UPROPERTY()
	UTexture2D* OutlinesMapTexture;
	
	UPROPERTY()
	UTexture2D* ProvincesMapTexture;

	FVector2D SizeVector;

	FColor OutlineColor = FColor(0, 0, 0);
	
	FColor BackgroundColor = FColor(255, 255, 255);
};
