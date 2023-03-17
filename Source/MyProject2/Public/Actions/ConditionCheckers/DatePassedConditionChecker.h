#pragma once
#include "ConditionChecker.h"
#include "InGameTime.h"

/**
 * @brief Event condition checker that checks if provided date have pass relatively to in game time 
 */
class FDatePassedConditionChecker : public FConditionChecker
{
public:
	FDatePassedConditionChecker(UInGameTime* GameTime);

	/**
	 *	@brief Method that checks date condition
	 *	@param Values - provided values, should have Year field - to represent desired year
	 *												 Month field - to represent desired month
	 *												 Day field - to represent desired day
	 *												 Hour field - to represent desired hour
	 */
	virtual bool Check(const TMap<FName, FString>& Values) override;

private:
	UInGameTime* GameTime;
};
