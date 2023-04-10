
#include "Actions/OutcomeAppliers/OutcomesApplierSubsystem.h"

#include "MyGameInstance.h"
#include "Actions/OutcomeAppliers/NonAlignedOutcomeApplier.h"

void UOutcomesApplierSubsystem::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UOutcomesApplierSubsystem::RegisterOutcomeApplier(const FName& Name, FOutcomeApplier* OutcomeApplier)
{
	OutcomeAppliers.Add(Name, OutcomeApplier);
}

void UOutcomesApplierSubsystem::ApplyOutcomes(TArray<FOutcome>& Outcomes, UCountryDescription* CountryDescription)
{
	for (auto& Outcome: Outcomes)
	{
		if (!OutcomeAppliers.Contains(Outcome.Name)) continue;
		bool AddedCountry = false;

		if (!Outcome.Values.Contains("Country"))
		{
			Outcome.Values.Add("Country", CountryDescription->Tag.ToString());
			AddedCountry = true;
		}

		OutcomeAppliers[Outcome.Name]->Apply(Outcome.Values);

		if (AddedCountry)
		{
			Outcome.Values.Remove("Country");
		}
	}
}

void UOutcomesApplierSubsystem::Clear()
{
	OutcomeAppliers.Empty();
}

void UOutcomesApplierSubsystem::Init(UScenario* Scenario)
{
	UCountriesManager* CountriesManager = GetGameInstance()->GetSubsystem<UCountriesManager>();
	RegisterOutcomeApplier("NonAlignment", new FNonAlignedOutcomeApplier(CountriesManager));
}
