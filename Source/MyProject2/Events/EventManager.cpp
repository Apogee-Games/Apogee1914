#include "EventManager.h"

FEventManager::~FEventManager()
{
	delete ConditionsChecker;
	delete InstancesController;
	delete OutcomesApplier;
}

void FEventManager::Tick() const
{
	InstancesController->Tick();
}

FEventManager::FEventManager(UDataTable* Events, const TSubclassOf<UEventWidget>& NewEventWidgetClass, UWorld* World): EventWidgetClass(NewEventWidgetClass)
{
	ConditionsChecker = new FEventConditionsChecker;
	OutcomesApplier = new FEventsOutcomesApplier;
	InstancesController = new FEventInstancesController(NewEventWidgetClass, this, World);

	for (const auto Pair : Events->GetRowMap())
	{
		this->Events.Add(Pair.Key.ToString(), reinterpret_cast<FEventDescription*>(Pair.Value));
	}
}

void FEventManager::CheckEvents()
{
	for (const auto& Pair: Events)
	{
		if (!ConditionsChecker->CheckConditions(Pair.Value->Conditions)) continue; // Skip current event because conditions are not meet 

		TMap<FString, bool> ChoicesConditionsEvaluated; // Holds results for choice condition check

		for (const auto& Choice: Pair.Value->Choices)
		{
			ChoicesConditionsEvaluated.Add(Choice.Name, ConditionsChecker->CheckConditions(Choice.Conditions));
		}
		
		InstancesController->CreateEventWidget(Pair.Key, Pair.Value, ChoicesConditionsEvaluated);
	}
}

void FEventManager::RegisterChoice(const FString& EventName, const FString& ChoiceName)
{
	// Removing Event widget
	InstancesController->DeleteEventWidget(EventName); 

	// Applying selected choice outcomes
	for (const auto& Choice: Events[EventName]->Choices)
	{
		if (Choice.Name != ChoiceName) continue;
		OutcomesApplier->ApplyOutcomes(Choice.Outcomes);
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
