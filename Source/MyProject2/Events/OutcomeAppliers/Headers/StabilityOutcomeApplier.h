#pragma once
#include "EventOutcomeApplier.h"
#include "MyProject2/MyGameState.h"

/**
 * Class used for testing
 * Updates stability
 */
class FStabilityOutcomeApplier: public FEventOutcomeApplier
{
public:
	/**
	 * Outcome applier needs GameState to access stability field
	 */
	explicit FStabilityOutcomeApplier(AMyGameState* GameState);

	/**
	 * Method updates stability with provided values
	 */
	virtual void Apply(TMap<FString, FString> Values) override;
	
	virtual ~FStabilityOutcomeApplier() override = default;
	
private:
	AMyGameState* GameState;
};
