#include "Events/OutcomeAppliers/StabilityOutcomeApplier.h"

#include "Kismet/KismetStringLibrary.h"

FStabilityOutcomeApplier::FStabilityOutcomeApplier(AMyGameState* GameState): GameState(GameState)
{
}

void FStabilityOutcomeApplier::Apply(const TMap<FName, FString>& Values)
{
	GameState->SetStability(GameState->GetStability() + UKismetStringLibrary::Conv_StringToInt(Values["Stability"]));
}
