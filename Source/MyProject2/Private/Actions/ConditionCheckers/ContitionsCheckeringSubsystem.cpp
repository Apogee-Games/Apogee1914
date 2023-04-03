#include "InGameTime.h"
#include "MyGameInstance.h"
#include "Actions/ConditionCheckers/ConditionsCheckingSubsystem.h"
#include "Actions/ConditionCheckers/DatePassedConditionChecker.h"
#include "Actions/ConditionCheckers/ExactDateConditionChecker.h"
#include "Actions/ConditionCheckers/NonAlignmentConditionChecker.h"
#include "Actions/Description/Condition.h"

bool UConditionsCheckingSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UConditionsCheckingSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	UInGameTime* InGameTime = GetWorld()->GetSubsystem<UInGameTime>();
	RegisterConditionChecker("ExactDate", new FExactDateConditionChecker(InGameTime));
	RegisterConditionChecker("DatePassed", new FDatePassedConditionChecker(InGameTime));

	UCountriesManager* CountriesManager = GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>();
	RegisterConditionChecker("NonAlignment", new FNonAlignmentConditionChecker(CountriesManager));
}

void UConditionsCheckingSubsystem::RegisterConditionChecker(const FName& Name, FConditionChecker* Checker)
{
	ConditionsCheckers.Add(Name, Checker);
}

bool UConditionsCheckingSubsystem::CheckConditions(TArray<FCondition>& Conditions, const FName& CountryTag)
{
	for (auto& Condition : Conditions)
	{
		if (!CheckCondition(Condition, CountryTag)) return false;
	}
	
	return true;
}

bool UConditionsCheckingSubsystem::CheckCondition(FCondition& Condition, const FName& CountryTag)
{
	if (!ConditionsCheckers.Contains(Condition.Name)) return false;
	bool AddedCountry = false;

	if (!Condition.Values.Contains("Country"))
	{
		Condition.Values.Add("Country", CountryTag.ToString());
		AddedCountry = true;
	}

	const bool HasPassed = ConditionsCheckers[Condition.Name]->Check(Condition.Values);

	if (AddedCountry)
	{
		Condition.Values.Remove("Country");
	}

	return HasPassed;
}