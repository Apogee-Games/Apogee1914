#include "Actions/ConditionCheckers/StabilityConditionChecker.h"

FStabilityConditionChecker::FStabilityConditionChecker(AGameLevelGameState* GameState): GameState(GameState)
{
}

bool FStabilityConditionChecker::Check(const TMap<FName, FString>& Values)
{
	return FString::FromInt(GameState->GetStability()) == Values["Stability"];
}
