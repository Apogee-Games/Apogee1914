#include "Events/ConditionCheckers/EventContitionsChecker.h"

#include "InGameTime.h"
#include "Events/ConditionCheckers/DatePassedConditionChecker.h"
#include "Events/ConditionCheckers/ExactDateConditionChecker.h"

void UEventConditionsChecker::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	UInGameTime* InGameTime = GetWorld()->GetSubsystem<UInGameTime>();
	RegisterConditionChecker("ExactDate", new FExactDateConditionChecker(InGameTime));
	RegisterConditionChecker("DatePassed", new FDatePassedConditionChecker(InGameTime));
}

void UEventConditionsChecker::RegisterConditionChecker(const FName& Name, FEventConditionChecker* Checker)
{
	ConditionsCheckers.Add(Name, Checker);
}

bool UEventConditionsChecker::CheckConditions(TArray<FEventCondition>& Conditions, const FName& CountryTag)
{
	for (auto& EventConditions : Conditions)
	{
		if (!ConditionsCheckers.Contains(EventConditions.Name)) return false;
		bool AddedCountry = false;

		if (!EventConditions.Values.Contains("Country"))
		{
			EventConditions.Values.Add("Country", CountryTag.ToString());
			AddedCountry = true;
		}

		const bool HasPassed = ConditionsCheckers[EventConditions.Name]->Check(EventConditions.Values);

		if (AddedCountry)
		{
			EventConditions.Values.Remove("Country");
		}

		if (!HasPassed) return false;
	}
	
	return true;
}