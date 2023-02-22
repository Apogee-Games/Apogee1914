#include "MyProject2/Events/ConditionCheckers/Headers/ExactDateConditionChecker.h"

FExactDateConditionChecker::FExactDateConditionChecker(UInGameTime* GameTime): GameTime(GameTime)
{
}

bool FExactDateConditionChecker::Check(TMap<FString, FString> Values)
{
	return GameTime->GetTime()->ToString(TEXT("%Y-%m-%d %H")) == Values["Date"];
}