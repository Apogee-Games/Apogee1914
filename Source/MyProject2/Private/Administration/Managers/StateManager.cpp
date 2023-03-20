
#include "Administration/Managers/StateManager.h"

#include "MyGameInstance.h"
#include "Scenario.h"
#include "LevelsOverides/Game/GameLevelGameState.h"


void UStateManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

UState* UStateManager::GetState(const FName& StateId) const
{
	return StateMap.Contains(StateId) ? StateMap[StateId] : nullptr;
}

bool UStateManager::AreProvincesInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const
{
	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	const UProvince* ProvinceA = ProvinceManager->GetProvince(ProvinceAColor);
	const UProvince* ProvinceB = ProvinceManager->GetProvince(ProvinceBColor);
	return AreProvincesInTheSameState(ProvinceA, ProvinceB);
}

bool UStateManager::AreProvincesInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const
{
	return ProvinceA && ProvinceB && ProvinceA->GetStateId() == ProvinceB->GetStateId();
}

bool UStateManager::AreProvincesNotInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const
{
	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	const UProvince* ProvinceA = ProvinceManager->GetProvince(ProvinceAColor);
	const UProvince* ProvinceB = ProvinceManager->GetProvince(ProvinceBColor);
	return AreProvincesNotInTheSameState(ProvinceA, ProvinceB);
}

bool UStateManager::AreProvincesNotInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const
{
	return ProvinceA && ProvinceB && ProvinceA->GetStateId() != ProvinceB->GetStateId();
}

void UStateManager::Clear()
{
	for (const auto& [Name, State]: StateMap)
	{
		State->MarkAsGarbage();
	}
	StateMap.Empty();
}

void UStateManager::Init(UScenario* Scenario)
{
	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();

	for (const auto& [Key, Value]: Scenario->StateDescriptionDataTable->GetRowMap())
	{
		UState* State = NewObject<UState>(this);
		State->Init(reinterpret_cast<FStateDescription*>(Value), ProvinceManager);
		StateMap.Add(Key, State);
	}
}
