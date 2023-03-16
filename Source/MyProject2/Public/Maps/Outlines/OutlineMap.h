#pragma once
#include "OutlineMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UOutlineMap: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	void CreateOutline();

	UPROPERTY(EditDefaultsOnly)
	FColor OutlineColor = FColor(0, 0, 0);
	
	UPROPERTY(EditDefaultsOnly)
	FColor BackgroundColor = FColor(255, 255, 255);
private:
	UPROPERTY()
	UTexture2D* OutlinesMapTexture;
	
	FVector2D SizeVector;
};
