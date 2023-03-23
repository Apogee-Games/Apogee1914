#include "Diplomacy/Interfaces/Observables/AllianceCreationObservable.h"

void IAllianceCreationObservable::NotifyAllianceCreation(UAlliance* Alliance)
{
	for (auto& Observer: Observers)
	{
		Observer->AllianceWasCreated(Alliance);
	}
}

bool IAllianceCreationObservable::AddAllianceCreationObserver(IAllianceCreationObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IAllianceCreationObservable::RemoveAllianceCreationObserver(IAllianceCreationObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
