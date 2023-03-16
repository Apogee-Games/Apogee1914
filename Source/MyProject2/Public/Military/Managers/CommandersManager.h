#pragma once
#include "Military/Interfaces/Commandable.h"
#include "People/Instances/Person.h"
#include "CommandersManager.generated.h"

UCLASS()
class UCommandersManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	void MakeCommander(UPerson* Person, ICommandable* Commandable);

	void RemoveCommander(ICommandable* Commandable);
private:
	TMap<UPerson*, ICommandable*> CommanderCommandable;
};
