#pragma once

class FOnFullInitialization
{
public:
	virtual ~FOnFullInitialization() = default;

	template <class T>
	void RegisterOnFullInitializationAction(T* Object, void (T::*Function)());

	virtual void RegisterOnFullInitializationAction(UObject* Object, void (UObject::*Function)());

	virtual void PerformOnFullInitializationActions();

protected:
	bool bIsFullyInitialized = false;

	TQueue<TPair<UObject*, void (UObject::*)()>> OnFullInitializationActions;
};

template <class T>
void FOnFullInitialization::RegisterOnFullInitializationAction(T* Object, void (T::* Function)())
{
	RegisterOnFullInitializationAction(static_cast<UObject*>(Object), static_cast<void (UObject::*)()>(Function));
}
