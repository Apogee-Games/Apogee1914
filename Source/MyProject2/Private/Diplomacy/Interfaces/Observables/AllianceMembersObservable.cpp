#include "Diplomacy/Interfaces/Observables/AllianceMembersObservable.h"

void IAllianceMembersObservable::NotifyMemberJoining(UCountry* Country)
{
	for (auto& Observer: Observers)
	{
		Observer->CountryHasJoinedAlliance(Country);
	}
}

bool IAllianceMembersObservable::AddAllianceMembersObserver(IAllianceMembersObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IAllianceMembersObservable::RemoveAllianceMembersObserver(IAllianceMembersObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
