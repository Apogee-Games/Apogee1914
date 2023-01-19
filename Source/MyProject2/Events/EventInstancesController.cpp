#include "EventInstancesController.h"

#include "EventManager.h"
#include "MyProject2/MyGameInstance.h"

FEventInstancesController::FEventInstancesController(const TSubclassOf<UEventWidget>& EventWidgetClass,
                                                     FEventManager* EventManager, UWorld* World,
                                                     AMyGameState* GameState):
	EventManager(EventManager), World(World), GameState(GameState), EventWidgetClass(EventWidgetClass)
{
}

void FEventInstancesController::Tick()
{
	AIEventsFiredRecently.Empty();
	for (const auto& Pair : WidgetsInstances)
	{
		Pair.Value->Tick();
	}
}

void FEventInstancesController::CreateEvent(const FString& EventName, const FEventDescription* Event,
                                            const TMap<FString, bool>& ChoicesConditionsEvaluated,
                                            const FString& CountryTag)
{
	if (WidgetsInstances.Contains({EventName, CountryTag})) return; // Event is already created 
	if (GameState->GetGameInstance<UMyGameInstance>()->IsCountryRuledByPlayer(CountryTag))
		CreateEventForPlayer(
			EventName, Event, ChoicesConditionsEvaluated, CountryTag);
	else CreateEventForAI(EventName, Event, ChoicesConditionsEvaluated, CountryTag);
}

void FEventInstancesController::DeleteEventWidget(const FString& EventName, const FString& CountryTag)
{
	if (!WidgetsInstances.Contains({EventName, CountryTag})) return; // Can't delete what doesn't exist

	WidgetsInstances[{EventName, CountryTag}]->RemoveFromParent(); // Remove from player screen

	WidgetsInstances.Remove({EventName, CountryTag});
	// Delete the only pointer to widget, so that it can be garbage collected
}

void FEventInstancesController::CreateEventForAI(const FString& EventName, const FEventDescription* Event,
                                                 const TMap<FString, bool>& ChoicesConditionsEvaluated,
                                                 const FString& CountryTag)
{
	if (AIEventsFiredRecently.Contains({EventName, CountryTag})) return;

	FiredEvents.Add(EventName); // Added this event to history of all events
	AIEventsFiredRecently.Add({EventName, CountryTag}); // Added this ai event to recently fired to avoid firing it again

	const FString AISelectedChoice = FindAISelectedChoice(Event->Choices, ChoicesConditionsEvaluated);
	
	EventManager->RegisterChoice(EventName, AISelectedChoice, CountryTag);
	
	for (const auto& c : CountryTag)
	{
		std::cout << static_cast<char>(c);
	}
	std::cout << " Selected ";
	for (const auto& c : AISelectedChoice)
	{
		std::cout << static_cast<char>(c);
	}
	std::cout << std::endl;
	
}

void FEventInstancesController::CreateEventForPlayer(const FString& EventName, const FEventDescription* Event,
                                                     const TMap<FString, bool>& ChoicesConditionsEvaluated,
                                                     const FString& CountryTag)
{
	FiredEvents.Add(EventName); // Added this event to history of all events

	UEventWidget* EventWidget = CreateWidget<UEventWidget>(World, EventWidgetClass);
	EventWidget->Init(Event->Title, Event->Text, Event->ImagePath);

	// Adding all choices that have their condition meet
	for (const auto& Choice : Event->Choices)
	{
		if (ChoicesConditionsEvaluated[Choice.Name])
		{
			EventWidget->AddChoice(EventName, Choice.Text, CountryTag, Choice.Text, EventManager);
		}
	}

	WidgetsInstances.Add({EventName, CountryTag}, EventWidget);
	EventWidget->AddToViewport();
}

inline float FEventInstancesController::CalculateSumOfAIChancesForChoices(const TArray<FEventChoice>& Choices, const TMap<FString, bool>& ChoicesConditionsEvaluated)
{
	float SummedChance = 0;
	for (const auto& Choice : Choices)
	{
		if (!ChoicesConditionsEvaluated[Choice.Name]) continue;
		SummedChance += Choice.AIChance;
	}
	return SummedChance;
}

FString FEventInstancesController::FindAISelectedChoice(const TArray<FEventChoice>& Choices, const TMap<FString, bool>& ChoicesConditionsEvaluated) const
{
	// Use Geometrical Probability to find which choice to select
	const float SummedChance = CalculateSumOfAIChancesForChoices(Choices, ChoicesConditionsEvaluated);

	FString SelectedChoice;
	
	float Point = FMath::FRandRange(0.0, SummedChance);
	for (const auto& Choice : Choices)
	{
		if (!ChoicesConditionsEvaluated[Choice.Name]) continue;

		if (Point <= Choice.AIChance)
		{
			SelectedChoice =  Choice.Name;
			break;
		}
		
		Point -= Choice.AIChance;
	}
	
	return SelectedChoice;
}
