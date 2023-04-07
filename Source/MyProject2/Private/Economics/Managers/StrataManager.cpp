#include "Economics/Managers//StrataManager.h"

#include "MyGameInstance.h"
#include "Engine/DataTable.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

void UStrataManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

FStrataDescription* UStrataManager::GetStrataDescription(const FName& Type) const
{
	return reinterpret_cast<FStrataDescription*>(StrataDescriptionDataTable->FindRowUnchecked(Type));
}

void UStrataManager::Clear()
{
	StrataDescriptionDataTable = nullptr;
}

void UStrataManager::Init(UScenario* Scenario)
{
	StrataDescriptionDataTable = Scenario->StrataDescriptionDataTable;
}

