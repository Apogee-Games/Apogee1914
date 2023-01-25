#include "MyProject2/Events/OutcomeAppliers/Headers/EventsOutcomesApplier.h"

void UEventsOutcomesApplier::RegisterOutcomeApplier(const FString& Name, FEventOutcomeApplier* OutcomeApplier)
{
	OutcomeAppliers.Add(Name, OutcomeApplier);
}

void UEventsOutcomesApplier::ApplyOutcomes(TArray<FEventOutcome>& Outcomes, const FString& CountryTag)
{
	for (auto& Outcome: Outcomes)
	{
		if (!OutcomeAppliers.Contains(Outcome.Name)) continue;
		bool AddedCountry = false;

		if (!Outcome.Values.Contains("Country"))
		{
			Outcome.Values.Add("Country", CountryTag);
			AddedCountry = true;
		}

		OutcomeAppliers[Outcome.Name]->Apply(Outcome.Values);

		if (AddedCountry)
		{
			Outcome.Values.Remove("Country");
		}
	}
}
