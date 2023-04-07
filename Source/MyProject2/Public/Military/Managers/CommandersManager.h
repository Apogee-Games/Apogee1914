#pragma once
#include "Scenario.h"
#include "Military/Interfaces/Commandable.h"
#include "People/Instances/Person.h"
#include "CommandersManager.generated.h"

UCLASS()
class UCommandersManager: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	void MakeCommander(UPerson* Person, ICommandable* Commandable);

	void RemoveCommander(ICommandable* Commandable);
private:
	TMap<UPerson*, ICommandable*> CommanderCommandable;

	void Clear();

	void Init(UScenario* Scenario);
};
