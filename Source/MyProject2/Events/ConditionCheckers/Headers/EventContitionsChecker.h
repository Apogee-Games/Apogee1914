#pragma once
#include "EventConditionChecker.h"
#include "MyProject2/Events/EventDescription/EventCondition.h"

/**
 * Class manages separate conditions checkers and allows to check event and choice conditions
 */
class FEventConditionsChecker
{
public:
	/**
	 *	Method used to add event condition checker
	 */
	void RegisterConditionChecker(const FString& Name, FEventConditionChecker* Checker);

	/**
	 * Method used to check event or choice conditions
	 */
	bool CheckConditions(const TArray<FEventCondition>& Conditions);

	~FEventConditionsChecker() = default;
private:
	TMap<FString, FEventConditionChecker*> ConditionsCheckers;
};
