#pragma once
#include "OutcomeApplier.h"
#include "MyGameState.h"
#include "MyProject2/Public/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Public/Administration/Managers/CountriesManager.h"
class FProvinceOccupierOutcomeApplier: FOutcomeApplier
{
public:

	FProvinceOccupierOutcomeApplier(UCountriesManager* CountriesManager,UProvinceManager* ProvinceManager);
	
	virtual void Apply(const TMap<FName, FString>& Values) override;
	
	virtual ~FProvinceOccupierOutcomeApplier() override = default;
	
private:
	UCountriesManager* CountriesManager;
	UProvinceManager* ProvinceManager;
};
