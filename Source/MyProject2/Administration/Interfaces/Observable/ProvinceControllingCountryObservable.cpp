#include "ProvinceControllingCountryObservable.h"


void IProvinceControllingCountryObservable::NotifyProvinceNewControllingCountry(UProvince* Province)
{
	for (auto& Observer: Observers)
	{
		Observer->ProvinceHasNewControllingCountry(Province);
	}
}

bool IProvinceControllingCountryObservable::AddProvinceControllingCountryObserver(IProvinceControllingCountryObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IProvinceControllingCountryObservable::RemoveProvinceControllingCountryObserver(IProvinceControllingCountryObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
