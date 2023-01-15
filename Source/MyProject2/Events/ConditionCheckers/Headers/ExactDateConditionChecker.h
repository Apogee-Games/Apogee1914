#pragma once
#include "EventConditionChecker.h"
#include "MyProject2/InGameTime.h"

/**
 * Checks current date
 */
class FExactDateConditionChecker: public FEventConditionChecker
{
public:
	/**
	 * Needs InGameTime to access current time
	 */
	explicit FExactDateConditionChecker(FInGameTime* GameTime);

	/**
	 *	Checks current data with provided values
	 */
	virtual bool Check(TMap<FString, FString> Values) override;

private:
	FInGameTime* GameTime;
};

