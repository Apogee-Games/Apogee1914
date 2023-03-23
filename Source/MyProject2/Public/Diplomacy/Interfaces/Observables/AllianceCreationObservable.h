#pragma once
#include "Diplomacy/Interfaces/Observers/AllianceCreationObserver.h"

class IAllianceCreationObservable
{
public:
	void NotifyAllianceCreation(UAlliance* Alliance);
	
	bool AddAllianceCreationObserver(IAllianceCreationObserver* Observer);
	
	bool RemoveAllianceCreationObserver(IAllianceCreationObserver* Observer);
private:
	TArray<IAllianceCreationObserver*> Observers;
};
