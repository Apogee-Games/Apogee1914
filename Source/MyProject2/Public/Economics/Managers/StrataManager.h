#pragma once
#include "Scenario.h"
#include "Economics/Description/StrataDescription.h"
#include "StrataManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UStrataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	const TArray<UStrataDescription*>& GetStratasDescriptions() const;
private:
	TArray<UStrataDescription*> StrataDescriptions;

	void Clear();

	void Init(UScenario* Scenario);
	
	// Need strata description
};
