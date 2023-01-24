#pragma once

/**
 *	Base class for event outcome appliers
 *	Task of such classes is to apply specific event outcome such as add stability, annex province etc 
 */
class FEventOutcomeApplier
{
public:
	/**
	 * Method to apply outcome with provided outcome values
	 */
	virtual void Apply(TMap<FString, FString> Values) = 0;

	virtual ~FEventOutcomeApplier() = default;
};
