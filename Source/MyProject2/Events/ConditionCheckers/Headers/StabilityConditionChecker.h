#pragma once
#include "EventConditionChecker.h"
#include "MyProject2/MyGameState.h"

/**
 * Class used for testing
 * Checks stability
 */
class FStabilityConditionChecker : public FEventConditionChecker
{
public:
	/**
	 * Conditions checker needs GameState to access stability field
	 */
	explicit FStabilityConditionChecker(AMyGameState* GameState);

	/**
	 * Method checks stability with provided values
	 */
	virtual bool Check(TMap<FString, FString> Values) override;

	virtual ~FStabilityConditionChecker() override = default;
private:
	AMyGameState* GameState;
};
