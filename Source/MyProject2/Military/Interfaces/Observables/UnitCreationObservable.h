#pragma once
#include "MyProject2/Military/Interfaces/Observers/UnitCreationObserver.h"

class IUnitCreationObservable
{
public:
	void NotifyUnitCreation(FUnit* Unit);
	
	bool AddUnitCreationObserver(IUnitCreationObserver* Observer);
	
	bool RemoveUnitCreationObserver(IUnitCreationObserver* Observer);
private:
	TArray<IUnitCreationObserver*> Observers;
};
