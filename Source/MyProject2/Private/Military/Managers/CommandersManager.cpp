#include "Military/Managers/CommandersManager.h"

void UCommandersManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UCommandersManager::MakeCommander(UPerson* Person, ICommandable* Commandable)
{
	RemoveCommander(Commandable);
	
	if (CommanderCommandable.Contains(Person))
	{
		RemoveCommander(CommanderCommandable[Person]);
	} 

	Commandable->SetCommander(Person);
	CommanderCommandable.Add(Person, Commandable);
}

void UCommandersManager::RemoveCommander(ICommandable* Commandable)
{
	if (!Commandable->GetCommander()) return;
	CommanderCommandable.Remove(Commandable->GetCommander());
	Commandable->SetCommander(nullptr);
}

void UCommandersManager::Clear()
{
	CommanderCommandable.Empty();
}

void UCommandersManager::Init(UScenario* Scenario)
{
}
