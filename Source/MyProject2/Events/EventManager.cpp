#include "EventManager.h"

#include "MyProject2/MyGameInstance.h"
#include "MyProject2/MyGameState.h"

FEventManager::~FEventManager()
{
	delete ConditionsChecker;
	delete InstancesController;
	delete OutcomesApplier;
}

TArray<FString>* FEventManager::GetCountriesForWhichEventCanBeFired(FEventDescription* Event) const
{
	return Event->CountriesConditions.ForAll
		       ? GameState->GetProvinceManager()->GetCountriesTagsList()
		       : &Event->CountriesConditions.CountriesTags;
}


void FEventManager::Tick(const FDateTime& CurrentInGameTime)
{
	if (LastDateEventWereChecked.GetTicks() == 0)
	{
		LastDateEventWereChecked = CurrentInGameTime;
	}
	if (CurrentInGameTime - LastDateEventWereChecked >= MinDeltaBetweenEventChecks)
	{
		CheckEvents();
		LastDateEventWereChecked = CurrentInGameTime;
	}

	InstancesController->Tick();
}

FEventManager::FEventManager(UDataTable* Events, const TSubclassOf<UEventWidget>& NewEventWidgetClass, UWorld* World,
                             AMyGameState* GameState, const FTimespan& MinDeltaBetweenEventChecks):
	MinDeltaBetweenEventChecks(MinDeltaBetweenEventChecks), GameState(GameState), EventWidgetClass(NewEventWidgetClass)
{
	ConditionsChecker = new FEventConditionsChecker;
	OutcomesApplier = new FEventsOutcomesApplier;
	InstancesController = new FEventInstancesController(NewEventWidgetClass, this, World, GameState);

	for (const auto Pair : Events->GetRowMap())
	{
		this->Events.Add(Pair.Key.ToString(), reinterpret_cast<FEventDescription*>(Pair.Value));
	}
}

void FEventManager::CheckEvents()
{
	for (const auto& Pair : Events)
	{
		TArray<FString>* CountriesTags = GetCountriesForWhichEventCanBeFired(Pair.Value);

		for (auto& CountryTag : *CountriesTags)
		{
			if (!ConditionsChecker->CheckConditions(Pair.Value->Conditions, CountryTag)) continue;
			// Skip current event because conditions are not meet 

			TMap<FString, bool> ChoicesConditionsEvaluated; // Holds results for choice condition check

			for (auto& Choice : Pair.Value->Choices)
			{
				ChoicesConditionsEvaluated.Add(Choice.Name,
				                               ConditionsChecker->CheckConditions(Choice.Conditions, CountryTag));
			}

			InstancesController->CreateEvent(Pair.Key, Pair.Value, ChoicesConditionsEvaluated, CountryTag);
		}
	}
}

void FEventManager::RegisterChoice(const FString& EventName, const FString& ChoiceName, const FString& CountryTag)
{
	// Removing Event widget
	InstancesController->DeleteEventWidget(EventName, CountryTag);

	// Applying selected choice outcomes
	for (auto& Choice : Events[EventName]->Choices)
	{
		if (Choice.Name != ChoiceName) continue;
		OutcomesApplier->ApplyOutcomes(Choice.Outcomes, CountryTag);
	}
}

void FEventManager::RegisterConditionChecker(const FString& Name, FEventConditionChecker* Checker) const
{
	ConditionsChecker->RegisterConditionChecker(Name, Checker);
}

void FEventManager::RegisterOutcomeApplier(const FString& Name, FEventOutcomeApplier* OutcomeApplier) const
{
	OutcomesApplier->RegisterOutcomeApplier(Name, OutcomeApplier);
}
