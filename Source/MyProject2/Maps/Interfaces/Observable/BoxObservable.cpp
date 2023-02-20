#include "BoxObservable.h"

void IBoxObservable::NotifyBoxUpdate(FProvincesBox* Box)
{
	for (auto& Observer: Observers)
	{
		Observer->BoxWasUpdated(Box);
	}
}

bool IBoxObservable::AddBoxObserver(IBoxObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IBoxObservable::RemoveBoxObserver(IBoxObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
