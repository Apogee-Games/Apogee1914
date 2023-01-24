#pragma once
#include "EventOutcomeApplier.h"
#include "MyProject2/Events/EventDescription/EventOutcome.h"

/**
 * Class manages separate outcome appliers and allows to apply choice outcomes
 */
class FEventsOutcomesApplier
{
public:
	/**
	 * Method used to add choice outcome applier
	 */
	void RegisterOutcomeApplier(const FString& Name, FEventOutcomeApplier* OutcomeApplier);

	/**
	 * Method used to apply event choice outcomes
	 */
	void ApplyOutcomes(TArray<FEventOutcome>& Outcomes, const FString& CountryTag);

	~FEventsOutcomesApplier() = default;
private:
	TMap<FString, FEventOutcomeApplier*> OutcomeAppliers;
};
