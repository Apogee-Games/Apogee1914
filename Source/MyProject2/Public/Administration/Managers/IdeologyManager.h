#pragma once
#include "Scenario.h"
#include "Administration/Instances/Ideology.h"

#include "IdeologyManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UIdeologyManager: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	UIdeology* GetIdeology(const FName& IdeologyTag);
private:
	UPROPERTY()
	TMap<FName, UIdeology*> IdeologiesMap;

	void Clear();

	void Init(UScenario* Scenario);
};