#include "MyProject2/Events/OutcomeAppliers/Headers/EventsOutcomesApplier.h"

void FEventsOutcomesApplier::RegisterOutcomeApplier(const FString& Name, FEventOutcomeApplier* OutcomeApplier)
{
	OutcomeAppliers.Add(Name, OutcomeApplier);
}

void FEventsOutcomesApplier::ApplyOutcomes(TArray<FEventOutcome> Outcomes)
{
	for (const auto& Outcome: Outcomes)
	{
		if (!OutcomeAppliers.Contains(Outcome.Name)) continue;
		OutcomeAppliers[Outcome.Name]->Apply(Outcome.Values);
	}
}
