#pragma once
#include "EventConditionChecker.h"
#include "MyProject2/InGameTime.h"

class FDatePassedConditionChecker : public FEventConditionChecker
{
public:
	FDatePassedConditionChecker(FInGameTime* GameTime);

	virtual bool Check(TMap<FString, FString> Values) override;

private:
	FInGameTime* GameTime;
};
