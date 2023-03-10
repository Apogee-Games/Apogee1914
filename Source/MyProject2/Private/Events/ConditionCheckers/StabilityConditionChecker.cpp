#include "Events/ConditionCheckers/StabilityConditionChecker.h"

FStabilityConditionChecker::FStabilityConditionChecker(AMyGameState* GameState): GameState(GameState)
{
}

bool FStabilityConditionChecker::Check(const TMap<FName, FString>& Values)
{
	return FString::FromInt(GameState->GetStability()) == Values["Stability"];
}
