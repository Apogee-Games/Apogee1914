#include "FOnFullInitialization.h"

void FOnFullInitialization::RegisterOnFullInitializationAction(UObject* Object, void(UObject::* Function)())
{
	if (bIsFullyInitialized)
	{
		(Object->*Function)();
		return;
	}
	OnFullInitializationActions.Enqueue({Object, Function});
}

void FOnFullInitialization::PerformOnFullInitializationActions()
{
	while (!OnFullInitializationActions.IsEmpty())
	{
		TPair<UObject*, void (UObject::*)()> Action;
		OnFullInitializationActions.Dequeue(Action);
		(Action.Key->*Action.Value)();
	}
}
