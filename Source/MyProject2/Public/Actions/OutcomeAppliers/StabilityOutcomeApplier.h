#pragma once
#include "OutcomeApplier.h"
#include "MyGameState.h"

/**
 * Class used for testing
 * Updates stability
 */
class FStabilityOutcomeApplier: public FOutcomeApplier
{
public:
	/**
	 * Outcome applier needs GameState to access stability field
	 */
	explicit FStabilityOutcomeApplier(AMyGameState* GameState);

	/**
	 * Method updates stability with provided values
	 */
	virtual void Apply(const TMap<FName, FString>& Values) override;
	
	virtual ~FStabilityOutcomeApplier() override = default;
	
private:
	AMyGameState* GameState;
};
