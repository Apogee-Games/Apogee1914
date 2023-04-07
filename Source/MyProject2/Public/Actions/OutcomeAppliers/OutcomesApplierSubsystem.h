#pragma once
#include "OutcomeApplier.h"
#include "Scenario.h"
#include "Actions/Description/Outcome.h"
#include "OutcomesApplierSubsystem.generated.h"
/**
 * Class manages separate outcome appliers and allows to apply choice outcomes
 */
UCLASS()
class UOutcomesApplierSubsystem: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	/**
	 * Method used to add choice outcome applier
	 */
	void RegisterOutcomeApplier(const FName& Name, FOutcomeApplier* OutcomeApplier);

	/**
	 * Method used to apply event choice outcomes
	 */
	void ApplyOutcomes(TArray<FOutcome>& Outcomes, const FName& CountryTag);
private:
	TMap<FName, FOutcomeApplier*> OutcomeAppliers;

	void Clear();

	void Init(UScenario* Scenario);
};
