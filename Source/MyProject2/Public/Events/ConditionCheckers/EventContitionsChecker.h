#pragma once
#include "EventConditionChecker.h"
#include "Events/EventDescription/EventCondition.h"
#include "EventContitionsChecker.generated.h"
/**
 * Class manages separate conditions checkers and allows to check event and choice conditions
 */
UCLASS()
class UEventConditionsChecker: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	/**
	 *	Method used to add event condition checker
	 */
	void RegisterConditionChecker(const FName& Name, FEventConditionChecker* Checker);

	/**
	 * Method used to check event or choice conditions
	 */
	bool CheckConditions(TArray<FEventCondition>& Conditions, const FName& CountryTag);

private:
	TMap<FName, FEventConditionChecker*> ConditionsCheckers;
};
