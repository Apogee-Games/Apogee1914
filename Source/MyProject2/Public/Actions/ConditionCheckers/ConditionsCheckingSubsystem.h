#pragma once
#include "ConditionChecker.h"
#include "Actions/Description/Condition.h"
#include "ConditionsCheckingSubsystem.generated.h"
/**
 * Class manages separate conditions checkers and allows to check event and choice conditions
 */
UCLASS()
class UConditionsCheckingSubsystem: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	/**
	 *	Method used to add event condition checker
	 */
	void RegisterConditionChecker(const FName& Name, FConditionChecker* Checker);

	/**
	 * Method used to check event or choice conditions
	 */
	bool CheckConditions(TArray<FCondition>& Conditions, const FName& CountryTag);

private:
	TMap<FName, FConditionChecker*> ConditionsCheckers;
};
