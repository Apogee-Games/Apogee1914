#pragma once
#include "MyProject2/Maps/Interfaces/Observer/BoxObserver.h"

class IBoxObservable
{
public:
	void NotifyBoxUpdate(TSharedPtr<FProvincesBox> Box);
	
	bool AddBoxObserver(IBoxObserver* Observer);
	
	bool RemoveBoxObserver(IBoxObserver* Observer);

private:
	TArray<IBoxObserver*> Observers;
};
