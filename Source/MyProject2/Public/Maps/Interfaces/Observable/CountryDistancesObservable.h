#pragma once
#include "Maps/Interfaces/Observer/CountryDistancesObserver.h"

class UProvince;

class ICountryDistancesObservable
{
public:
	void NotifyCountryDistancesUpdate(const TArray<UProvince*>& Provinces);
	
	bool AddCountryDistancesObserver(ICountryDistancesObserver* Observer);
	
	bool RemoveCountryDistancesObserver(ICountryDistancesObserver* Observer);

private:
	TArray<ICountryDistancesObserver*> Observers;
};
