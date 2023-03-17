#pragma once
#include "OutcomeApplier.h"
#include "Actions/Description/Outcome.h"
#include "OutcomesApplierSubsystem.generated.h"
/**
 * Class manages separate outcome appliers and allows to apply choice outcomes
 */
UCLASS()
class UOutcomesApplierSubsystem: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	/**
	 * Method used to add choice outcome applier
	 */
	void RegisterOutcomeApplier(const FName& Name, FOutcomeApplier* OutcomeApplier);

	/**
	 * Method used to apply event choice outcomes
	 */
	void ApplyOutcomes(TArray<FOutcome>& Outcomes, const FName& CountryTag);
private:
	TMap<FName, FOutcomeApplier*> OutcomeAppliers;
};
