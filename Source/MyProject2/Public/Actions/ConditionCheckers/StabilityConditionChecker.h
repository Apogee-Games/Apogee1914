#pragma once
#include "ConditionChecker.h"
#include "MyGameState.h"

/**
 * Class used for testing
 * Checks stability
 */
class FStabilityConditionChecker : public FConditionChecker
{
public:
	/**
	 * Conditions checker needs GameState to access stability field
	 */
	explicit FStabilityConditionChecker(AMyGameState* GameState);

	/**
	 * Method checks stability with provided values
	 */
	virtual bool Check(const TMap<FName, FString>& Values) override;

	virtual ~FStabilityConditionChecker() override = default;
private:
	AMyGameState* GameState;
};
