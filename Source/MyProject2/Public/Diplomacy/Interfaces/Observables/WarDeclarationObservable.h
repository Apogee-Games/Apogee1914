#pragma once
#include "Diplomacy/Instances/War.h"
#include "Diplomacy/Interfaces/Observers/WarDeclarationObserver.h"

class IWarDeclarationObservable
{
public:
	void NotifyWarDeclaration(UWar* War);
	
	bool AddWarDeclarationObserver(IWarDeclarationObserver* Observer);
	
	bool RemoveWarDeclarationObserver(IWarDeclarationObserver* Observer);
private:
	TArray<IWarDeclarationObserver*> Observers;
};
