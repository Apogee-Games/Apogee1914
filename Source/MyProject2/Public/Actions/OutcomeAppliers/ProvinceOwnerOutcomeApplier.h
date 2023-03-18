#pragma once
#include "OutcomeApplier.h"
#include "MyProject2/Public/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Public/Administration/Managers/CountriesManager.h"

class FProvinceOwnerOutcomeApplier: public FOutcomeApplier
{
public:
	FProvinceOwnerOutcomeApplier(UCountriesManager* CountriesManager,UProvinceManager* ProvinceManager);
	
	virtual void Apply(const TMap<FName, FString>& Values) override;
	
	virtual ~FProvinceOwnerOutcomeApplier() override = default;
private:
	UCountriesManager* CountriesManager;
	
	UProvinceManager* ProvinceManager;
};