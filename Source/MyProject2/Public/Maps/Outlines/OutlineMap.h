#pragma once
#include "Scenario.h"
#include "OutlineMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UOutlineMap: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
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
