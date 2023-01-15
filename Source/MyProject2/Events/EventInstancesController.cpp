#include "EventInstancesController.h"

FEventInstancesController::FEventInstancesController(const TSubclassOf<UEventWidget>& EventWidgetClass,
	FEventManager* EventManager, UWorld* World):
	EventManager(EventManager), World(World), EventWidgetClass(EventWidgetClass)
{
}

void FEventInstancesController::Tick()
{
	for (const auto& Pair: WidgetsInstances)
	{
		Pair.Value->Tick();
	}
}

void FEventInstancesController::CreateEventWidget(const FString& EventName, const FEventDescription* Event, const TMap<FString, bool>& ChoicesConditionsEvaluated)
{
	if (WidgetsInstances.Contains(EventName)) return; // Event is already created 

	FiredEvents.Add(EventName); // Added this event to history of all events

	UEventWidget* EventWidget = CreateWidget<UEventWidget>(World, EventWidgetClass);
	EventWidget->Init(Event->Title, Event->Text, Event->ImagePath);

	// Adding all choices that have their condition meet
	for (const auto& Choice : Event->Choices)
	{
		if (ChoicesConditionsEvaluated[Choice.Name])
		{
			EventWidget->AddChoice(EventName, Choice.Text, Choice.Text, EventManager);
		}
	}

	WidgetsInstances.Add(EventName, EventWidget);
	EventWidget->AddToViewport();
}

void FEventInstancesController::DeleteEventWidget(const FString& EventName)
{
	if (!WidgetsInstances.Contains(EventName)) return; // Can't delete what doesn't exist

	WidgetsInstances[EventName]->RemoveFromParent(); // Remove from player screen
		
	WidgetsInstances.Remove(EventName); // Delete the only pointer to widget, so that it can be garbage collected
}
