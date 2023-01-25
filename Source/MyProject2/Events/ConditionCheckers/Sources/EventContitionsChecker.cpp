#include "MyProject2/Events/ConditionCheckers/Headers/EventContitionsChecker.h"

void UEventConditionsChecker::RegisterConditionChecker(const FString& Name, FEventConditionChecker* Checker)
{
	ConditionsCheckers.Add(Name, Checker);
}

bool UEventConditionsChecker::CheckConditions(TArray<FEventCondition>& Conditions, const FString& CountryTag)
{
	for (auto& EventConditions : Conditions)
	{
		if (!ConditionsCheckers.Contains(EventConditions.Name)) return false;
		bool AddedCountry = false;

		if (!EventConditions.Values.Contains("Country"))
		{
			EventConditions.Values.Add("Country", CountryTag);
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