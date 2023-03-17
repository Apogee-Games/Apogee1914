#pragma once

/**
 *	Base class for event condition checkers
 *	Task of such classes is to check specific event condition such as exact date, province owned etc 
 */
class FConditionChecker
{
public:
	/**
	 * Method used to check event condition with specific values
	 */
	virtual bool Check(const TMap<FName, FString>& Values) = 0;

	virtual ~FConditionChecker() = default;
};
