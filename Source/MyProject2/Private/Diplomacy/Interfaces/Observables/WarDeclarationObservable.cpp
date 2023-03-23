#include "Diplomacy/Interfaces/Observables/WarDeclarationObservable.h"

void IWarDeclarationObservable::NotifyWarDeclaration(UWar* War)
{
	for (auto& Observer: Observers)
	{
		Observer->WarWasDeclared(War);
	}
}

bool IWarDeclarationObservable::AddWarDeclarationObserver(IWarDeclarationObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IWarDeclarationObservable::RemoveWarDeclarationObserver(IWarDeclarationObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
