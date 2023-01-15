#pragma once
#include "EventDescription/EventDescription.h"
#include "MyProject2/Widgets/EventWidget.h"

class FEventManager;

/**
 * Class used to control all events instances
 */ 
class FEventInstancesController
{
public:
	FEventInstancesController(const TSubclassOf<UEventWidget>& EventWidgetClass, FEventManager* EventManager, UWorld* World);

	/**
	 *	Method for all per frame updates such as events widgets moving 
	 */
	void Tick();

	/**
	 * Creates and displays event widget with required data
	 */
	void CreateEventWidget(const FString& EventName, const FEventDescription* Event, const TMap<FString, bool>& ChoicesConditionsEvaluated);

	/**
	 *	Removes event widget 
	 */
	void DeleteEventWidget(const FString& EventName);

	~FEventInstancesController() = default;

private:
	FEventManager* EventManager;

	UWorld* World;

	TSet<FString> FiredEvents;

	TMap<FString, bool> ActiveEvents;

	TSubclassOf<UEventWidget> EventWidgetClass;

	TMap<FString, UEventWidget*> WidgetsInstances;
};
