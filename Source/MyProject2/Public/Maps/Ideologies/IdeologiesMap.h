#pragma once
#include "Scenario.h"

#include "IdeologiesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UIdeologiesMap: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);

	void UpdateMap();
private:
	UPROPERTY()
	UTexture2D* IdeologiesMapTexture;
	
	void Clear();

	void Init(UScenario* Scenario);
};
