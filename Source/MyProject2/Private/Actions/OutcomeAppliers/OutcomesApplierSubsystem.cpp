
#include "Actions/OutcomeAppliers/OutcomesApplierSubsystem.h"

#include "MyGameInstance.h"
#include "Actions/OutcomeAppliers/NonAlignedOutcomeApplier.h"

bool UOutcomesApplierSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UOutcomesApplierSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	UCountriesManager* CountriesManager = GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>();
	RegisterOutcomeApplier("NonAlignment", new FNonAlignedOutcomeApplier(CountriesManager));
}

void UOutcomesApplierSubsystem::RegisterOutcomeApplier(const FName& Name, FOutcomeApplier* OutcomeApplier)
{
	OutcomeAppliers.Add(Name, OutcomeApplier);
}

void UOutcomesApplierSubsystem::ApplyOutcomes(TArray<FOutcome>& Outcomes, const FName& CountryTag)
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
