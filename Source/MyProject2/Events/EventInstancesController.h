#pragma once
#include "EventDescription/EventDescription.h"
#include "MyProject2/MyGameState.h"
#include "MyProject2/Widgets/EventWidget.h"

class FEventManager;

/**
 * Class used to control all events instances
 */ 
class FEventInstancesController
{
public:
	FEventInstancesController(const TSubclassOf<UEventWidget>& EventWidgetClass, FEventManager* EventManager, UWorld* World, AMyGameState* GameState);

	/**
	 *	Method for all per frame updates such as events widgets moving 
	 */
	void Tick();

	/**
	 * Creates and displays event widget with required data
	 */
	void CreateEvent(const FString& EventName, const FEventDescription* Event, const TMap<FString, bool>& ChoicesConditionsEvaluated, const FString& CountryTag);

	/**
	 *	Removes event widget 
	 */
	void DeleteEventWidget(const FString& EventName, const FString& CountryTag);

	~FEventInstancesController() = default;

private:
	FEventManager* EventManager;

	UWorld* World;

	AMyGameState* GameState;
	
	TSet<FString> FiredEvents;

	TMap<FString, bool> ActiveEvents;

	TSubclassOf<UEventWidget> EventWidgetClass;

	TMap<TPair<FString, FString>, UEventWidget*> WidgetsInstances;

	void CreateEventForAI(const FString& EventName, const FEventDescription* Event, const TMap<FString, bool>& ChoicesConditionsEvaluated, const FString& CountryTag);
	
	void CreateEventForPlayer(const FString& EventName, const FEventDescription* Event, const TMap<FString, bool>& ChoicesConditionsEvaluated, const FString& CountryTag);

	static float CalculateSumOfAIChancesForChoices(const TArray<FEventChoice>& Choices, const TMap<FString, bool>& ChoicesConditionsEvaluated);

	FString FindAISelectedChoice(const TArray<FEventChoice>& Choices, const TMap<FString, bool>& ChoicesConditionsEvaluated) const;
};