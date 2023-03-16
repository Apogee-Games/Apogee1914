#include "Events/OutcomeAppliers/EventsOutcomesApplier.h"

#include "Events/OutcomeAppliers/StabilityOutcomeApplier.h"

void UEventsOutcomesApplier::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	RegisterOutcomeApplier("Stability", new FStabilityOutcomeApplier(GetWorld()->GetGameState<AGameLevelGameState>()));
}

void UEventsOutcomesApplier::RegisterOutcomeApplier(const FName& Name, FEventOutcomeApplier* OutcomeApplier)
{
	OutcomeAppliers.Add(Name, OutcomeApplier);
}

void UEventsOutcomesApplier::ApplyOutcomes(TArray<FEventOutcome>& Outcomes, const FName& CountryTag)
{
	for (auto& Outcome: Outcomes)
	{
		if (!OutcomeAppliers.Contains(Outcome.Name)) continue;
		bool AddedCountry = false;

		if (!Outcome.Values.Contains("Country"))
		{
			Outcome.Values.Add("Country", CountryTag.ToString());
			AddedCountry = true;
		}

		OutcomeAppliers[Outcome.Name]->Apply(Outcome.Values);

		if (AddedCountry)
		{
			Outcome.Values.Remove("Country");
		}
	}
}
