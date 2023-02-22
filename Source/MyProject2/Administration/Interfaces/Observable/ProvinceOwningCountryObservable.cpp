#include "ProvinceOwningCountryObservable.h"


void IProvinceOwningCountryObservable::NotifyProvinceNewOwningCountry(UProvince* Province)
{
	for (auto& Observer: Observers)
	{
		Observer->ProvinceHasNewOwningCountry(Province);
	}
}

bool IProvinceOwningCountryObservable::AddProvinceOwningCountryObserver(IProvinceOwningCountryObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IProvinceOwningCountryObservable::RemoveProvinceOwningCountryObserver(IProvinceOwningCountryObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
