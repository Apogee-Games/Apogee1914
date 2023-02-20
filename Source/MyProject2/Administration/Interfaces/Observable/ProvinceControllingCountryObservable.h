#pragma once
#include "MyProject2/Administration/Interfaces/Observer/ProvinceControllingCountryObserver.h"

class UProvince;

class IProvinceControllingCountryObservable
{
public:
	void NotifyProvinceNewControllingCountry(UProvince* Unit);
	
	bool AddProvinceControllingCountryObserver(IProvinceControllingCountryObserver* Observer);
	
	bool RemoveProvinceControllingCountryObserver(IProvinceControllingCountryObserver* Observer);

private:
	TArray<IProvinceControllingCountryObserver*> Observers;
};
