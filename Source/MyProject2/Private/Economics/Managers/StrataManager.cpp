#include "Economics/Managers//StrataManager.h"

#include "MyGameInstance.h"
#include "Engine/DataTable.h"

void UStrataManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

const TArray<UStrataDescription*>& UStrataManager::GetStratasDescriptions() const
{
	return StrataDescriptions;	
}

ELoadStage UStrataManager::GetLoadStage()
{
	return ELoadStage::StrataManager;
}

void UStrataManager::Clear()
{
	StrataDescriptions.Empty();
}

void UStrataManager::Init(UScenario* Scenario)
{
	StrataDescriptions = Scenario->StrataDescriptions;
}

