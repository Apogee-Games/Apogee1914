
#include "Administration/Managers/StateManager.h"

#include "MyGameInstance.h"
#include "Scenario.h"
#include "LevelsOverides/Game/GameLevelGameState.h"


void UStateManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

UState* UStateManager::GetState(UStateDescription* StateDescription) const
{
	return StateMap.Contains(StateDescription) ? StateMap[StateDescription] : nullptr;
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
	return ProvinceA && ProvinceB && ProvinceA->GetState() == ProvinceB->GetState();
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
	return ProvinceA && ProvinceB && ProvinceA->GetState() != ProvinceB->GetState();
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

	for (const auto& Description: Scenario->StatesDescriptions)
	{
		UState* State = NewObject<UState>(this);
		State->Init(Description);
		StateMap.Add(Description, State);
	}
}
