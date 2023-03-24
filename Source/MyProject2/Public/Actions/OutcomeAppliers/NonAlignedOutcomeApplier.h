#pragma once
#include "OutcomeApplier.h"
#include "Administration/Managers/CountriesManager.h"

class FNonAlignedOutcomeApplier: public FOutcomeApplier
{
public:
	explicit FNonAlignedOutcomeApplier(UCountriesManager* CountriesManager);
	
	virtual void Apply(const TMap<FName, FString>& Values) override;
private:
	UCountriesManager* CountriesManager;
};
