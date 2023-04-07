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
	
	FStrataDescription* GetStrataDescription(const FName& Type) const;
private:
	UPROPERTY()
	UDataTable* StrataDescriptionDataTable;

	void Clear();

	void Init(UScenario* Scenario);
	
	// Need strata description
};
