#pragma once
#include "EventOutcomeApplier.h"
#include "Events/EventDescription/EventOutcome.h"
#include "EventsOutcomesApplier.generated.h"
/**
 * Class manages separate outcome appliers and allows to apply choice outcomes
 */
UCLASS()
class UEventsOutcomesApplier: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	/**
	 * Method used to add choice outcome applier
	 */
	void RegisterOutcomeApplier(const FName& Name, FEventOutcomeApplier* OutcomeApplier);

	/**
	 * Method used to apply event choice outcomes
	 */
	void ApplyOutcomes(TArray<FEventOutcome>& Outcomes, const FName& CountryTag);

private:
	TMap<FName, FEventOutcomeApplier*> OutcomeAppliers;
};