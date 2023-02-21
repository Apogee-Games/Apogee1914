#include "MyProject2/Events/ConditionCheckers/Headers/StabilityConditionChecker.h"

FStabilityConditionChecker::FStabilityConditionChecker(AMyGameState* GameState): GameState(GameState)
{
}

bool FStabilityConditionChecker::Check(TMap<FName, FString> Values)
{
	return FString::FromInt(GameState->GetStability()) == Values["Stability"];
}
