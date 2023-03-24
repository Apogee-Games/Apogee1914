#pragma once
#include "ConditionChecker.h"
#include "Administration/Managers/CountriesManager.h"

class FNonAlignmentConditionChecker: public FConditionChecker
{
public:
	explicit FNonAlignmentConditionChecker(UCountriesManager* CountriesManager);
	
	virtual bool Check(const TMap<FName, FString>& Values) override;
private:
	UCountriesManager* CountriesManager;
};
