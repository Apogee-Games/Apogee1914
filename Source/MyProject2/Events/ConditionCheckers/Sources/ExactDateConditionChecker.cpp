#include "MyProject2/Events/ConditionCheckers/Headers/ExactDateConditionChecker.h"

FExactDateConditionChecker::FExactDateConditionChecker(FInGameTime* GameTime): GameTime(GameTime)
{
}

bool FExactDateConditionChecker::Check(TMap<FString, FString> Values)
{
	return GameTime->GetTime()->ToString(TEXT("%Y-%m-%d %H")) == Values["Date"];
}