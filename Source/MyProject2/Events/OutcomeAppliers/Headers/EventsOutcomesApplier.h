#pragma once
#include "EventOutcomeApplier.h"
#include "MyProject2/Events/EventDescription/EventOutcome.h"
#include "EventsOutcomesApplier.generated.h"
/**
 * Class manages separate outcome appliers and allows to apply choice outcomes
 */
UCLASS()
class UEventsOutcomesApplier: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	/**
	 * Method used to add choice outcome applier
	 */
	void RegisterOutcomeApplier(const FString& Name, FEventOutcomeApplier* OutcomeApplier);

	/**
	 * Method used to apply event choice outcomes
	 */
	void ApplyOutcomes(TArray<FEventOutcome>& Outcomes, const FString& CountryTag);

private:
	TMap<FString, FEventOutcomeApplier*> OutcomeAppliers;
};
