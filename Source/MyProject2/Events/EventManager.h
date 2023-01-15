#pragma once
#include "MyProject2/Widgets/EventWidget.h"
#include "EventInstancesController.h"
#include "ConditionCheckers/Headers/EventConditionChecker.h"
#include "ConditionCheckers/Headers/EventContitionsChecker.h"
#include "OutcomeAppliers/Headers/EventOutcomeApplier.h"
#include "OutcomeAppliers/Headers/EventsOutcomesApplier.h"

/**
 * FEventManager is responsible for all Events logic 
 */
class FEventManager
{
public:
	
	FEventManager(UDataTable* Events, const TSubclassOf<UEventWidget>& NewEventWidgetClass, UWorld* World);

	/**
	 *	Method to check all events and fire those that pass all conditions
	 */
	void CheckEvents();

	/**
	 *	Method for all per frame updates
	 */
	void Tick() const;

	/**
	 *	Method used to record selected choice for specific event
	 */
	void RegisterChoice(const FString& EventName, const FString& ChoiceName);

	/**
	 *	Method used to add event condition checker
	 */
	void RegisterConditionChecker(const FString& Name, FEventConditionChecker* Checker) const;

	/**
	 * Method used to add choice outcome applier
	 */
	void RegisterOutcomeApplier(const FString& Name, FEventOutcomeApplier* OutcomeApplier) const;

	~FEventManager();
private:
	FEventConditionsChecker* ConditionsChecker;

	FEventInstancesController* InstancesController;

	FEventsOutcomesApplier* OutcomesApplier;

	TSubclassOf<UEventWidget> EventWidgetClass;

	TMap<FString, FEventDescription*> Events;
};
