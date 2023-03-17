#pragma once
#include "OutcomeApplier.h"
#include "MyProject2/Public/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Public/Administration/Managers/CountriesManager.h"

class FProvinceControllerOutcomeApplier: public FOutcomeApplier
{
public:
	FProvinceControllerOutcomeApplier(UCountriesManager* CountriesManager,UProvinceManager* ProvinceManager);
	
	virtual void Apply(const TMap<FName, FString>& Values) override;
	
	virtual ~FProvinceControllerOutcomeApplier() override = default;
private:
	UCountriesManager* CountriesManager;
	
	UProvinceManager* ProvinceManager;
};
