#pragma once
#include "MyProject2/Military/Interfaces/Observers/UnitMovementObserver.h"

class IUnitMovementObservable
{
public:
	void NotifyUnitMovement(FUnit* Unit, UProvince* From, UProvince* To);

	bool AddUnitMovementObserver(IUnitMovementObserver* Observer);
	
	bool RemoveUnitMovementObserver(IUnitMovementObserver* Observer);
private:
	TArray<IUnitMovementObserver*> Observers;
};
