#pragma once
#include "Scenario.h"
#include "Interfaces/BaseManager.h"
#include "Military/Interfaces/Commandable.h"
#include "People/Instances/Person.h"
#include "CommandersManager.generated.h"

UCLASS()
class UCommandersManager: public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	void MakeCommander(UPerson* Person, ICommandable* Commandable);

	void RemoveCommander(ICommandable* Commandable);

	virtual ELoadStage GetLoadStage() override;
private:
	TMap<UPerson*, ICommandable*> CommanderCommandable;

	void Clear();

	void Init(UScenario* Scenario);
};
