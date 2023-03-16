
#include "Administration/Managers/StateManager.h"

#include "MyGameInstance.h"
#include "Scenario.h"
#include "LevelsOverides/Game/GameLevelGameState.h"


bool UStateManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UStateManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UDataTable* StateDescriptionDataTable = GetWorld()->GetGameInstance<UMyGameInstance>()->ActiveScenario->StateDescriptionDataTable; 
	InitStates(StateDescriptionDataTable);
}

UState* UStateManager::GetState(const FName& StateId) const
{
	return StateMap.Contains(StateId) ? StateMap[StateId] : nullptr;
}

bool UStateManager::AreProvincesInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const
{
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
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
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	const UProvince* ProvinceA = ProvinceManager->GetProvince(ProvinceAColor);
	const UProvince* ProvinceB = ProvinceManager->GetProvince(ProvinceBColor);
	return AreProvincesNotInTheSameState(ProvinceA, ProvinceB);
}

bool UStateManager::AreProvincesNotInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const
{
	return ProvinceA && ProvinceB && ProvinceA->GetStateId() != ProvinceB->GetStateId();
}

void UStateManager::InitStates(UDataTable* StatesDescriptions)
{
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();

	for (const auto& [Key, Value]: StatesDescriptions->GetRowMap())
	{
		UState* State = NewObject<UState>();
		State->Init(reinterpret_cast<FStateDescription*>(Value), ProvinceManager);
		StateMap.Add(Key, State);
	}
}
