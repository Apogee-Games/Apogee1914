#pragma once
#include "Military/Interfaces/Observers/UnitCreationObserver.h"

class IUnitCreationObservable
{
public:
	void NotifyUnitCreation(UUnit* Unit);
	
	bool AddUnitCreationObserver(IUnitCreationObserver* Observer);
	
	bool RemoveUnitCreationObserver(IUnitCreationObserver* Observer);
private:
	TArray<IUnitCreationObserver*> Observers;
};
