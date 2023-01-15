#include "MyProject2/Events/ConditionCheckers/Headers/EventContitionsChecker.h"

void FEventConditionsChecker::RegisterConditionChecker(const FString& Name, FEventConditionChecker* Checker)
{
	ConditionsCheckers.Add(Name, Checker);
}

bool FEventConditionsChecker::CheckConditions(const TArray<FEventCondition>& Conditions)
{
	for (const auto& EventConditions : Conditions)
	{
		if (!ConditionsCheckers.Contains(EventConditions.Name)) return false;
		if (!ConditionsCheckers[EventConditions.Name]->Check(EventConditions.Values)) return false;
	}
	return true;
}
