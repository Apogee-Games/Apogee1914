#pragma once
#include "ConditionChecker.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

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
	explicit FStabilityConditionChecker(AGameLevelGameState* GameState);

	/**
	 * Method checks stability with provided values
	 */
	virtual bool Check(const TMap<FName, FString>& Values) override;

	virtual ~FStabilityConditionChecker() override = default;
private:
	AGameLevelGameState* GameState;
};
