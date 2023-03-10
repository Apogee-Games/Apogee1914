

#include "Maps/Interfaces/Observable/CountryDistancesObservable.h"

void ICountryDistancesObservable::NotifyCountryDistancesUpdate(const TArray<UProvince*>& Provinces)
{
	for (auto& Observer: Observers)
	{
		Observer->CountryDistancesWereUpdated(Provinces);
	}
}

bool ICountryDistancesObservable::AddCountryDistancesObserver(ICountryDistancesObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool ICountryDistancesObservable::RemoveCountryDistancesObserver(ICountryDistancesObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
