#pragma once
#include "Administration/Interfaces/Observer/ProvinceOwningCountryObserver.h"

class UProvince;

class IProvinceOwningCountryObservable
{
public:
	void NotifyProvinceNewOwningCountry(UProvince* Unit);
	
	bool AddProvinceOwningCountryObserver(IProvinceOwningCountryObserver* Observer);
	
	bool RemoveProvinceOwningCountryObserver(IProvinceOwningCountryObserver* Observer);

private:
	TArray<IProvinceOwningCountryObserver*> Observers;
};
