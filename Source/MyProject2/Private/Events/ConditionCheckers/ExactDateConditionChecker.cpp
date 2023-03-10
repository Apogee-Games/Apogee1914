#include "Events/ConditionCheckers/ExactDateConditionChecker.h"

FExactDateConditionChecker::FExactDateConditionChecker(UInGameTime* GameTime): GameTime(GameTime)
{
}

bool FExactDateConditionChecker::Check(const TMap<FName, FString>& Values)
{
	return GameTime->GetTime().ToString(TEXT("%Y-%m-%d %H")) == Values["Date"];
}