#pragma once
#include "Scenario.h"
#include "Economics/Description/StrataDescription.h"
#include "Interfaces/BaseManager.h"
#include "StrataManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UStrataManager : public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	const TArray<UStrataDescription*>& GetStratasDescriptions() const;

	virtual ELoadStage GetLoadStage() override;
private:
	TArray<UStrataDescription*> StrataDescriptions;

	void Clear();

	void Init(UScenario* Scenario);
	
	// Need strata description
};
