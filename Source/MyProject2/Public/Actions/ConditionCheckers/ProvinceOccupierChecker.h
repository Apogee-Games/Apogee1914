
#pragma once
#include "ConditionChecker.h"
#include "MyGameState.h"
#include "MyProject2/Public/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Public/Administration/Managers/CountriesManager.h"

class FProvinceOccupierConditionChecker: public FConditionChecker
{
public:
	FProvinceOccupierConditionChecker(UCountriesManager* CountriesManager,UProvinceManager* ProvinceManager);


	virtual bool Check(const TMap<FName, FString>& Values) override;

private:
	UCountriesManager* CountriesManager;
	UProvinceManager* ProvinceManager;
};
