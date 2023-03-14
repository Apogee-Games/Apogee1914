#include "InGameTime.h"
#include "Actions/ConditionCheckers/ConditionsCheckingSubsystem.h"
#include "Actions/ConditionCheckers/DatePassedConditionChecker.h"
#include "Actions/ConditionCheckers/ExactDateConditionChecker.h"
#include "Actions/Description/Condition.h"

void UConditionsCheckingSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	UInGameTime* InGameTime = GetWorld()->GetSubsystem<UInGameTime>();
	RegisterConditionChecker("ExactDate", new FExactDateConditionChecker(InGameTime));
	RegisterConditionChecker("DatePassed", new FDatePassedConditionChecker(InGameTime));
}

void UConditionsCheckingSubsystem::RegisterConditionChecker(const FName& Name, FConditionChecker* Checker)
{
	ConditionsCheckers.Add(Name, Checker);
}

bool UConditionsCheckingSubsystem::CheckConditions(TArray<FCondition>& Conditions, const FName& CountryTag)
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