#pragma once
#include "EventConditionChecker.h"
#include "MyProject2/InGameTime.h"

/**
 * Checks current date
 * Unreliable condition because there is no guarantee that events will be checked at exact date.
 * So it is better to DatePassed
 */
class FExactDateConditionChecker: public FEventConditionChecker
{
public:
	/**
	 * Needs InGameTime to access current time
	 */
	explicit FExactDateConditionChecker(UInGameTime* GameTime);

	/**
	 *	@brief Checks current data with provided values
	 *	@param Values - provided values, should have Date field to represent desired date
	 */
	virtual bool Check(const TMap<FName, FString>& Values) override;

private:
	UInGameTime* GameTime;
};

