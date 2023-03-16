#include "Economics/Managers//StrataManager.h"

#include "MyGameInstance.h"
#include "Engine/DataTable.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

bool UStrataManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UStrataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	StrataDescriptionDataTable = GetWorld()->GetGameInstance<UMyGameInstance>()->ActiveScenario->StrataDescriptionDataTable;
}

FStrataDescription* UStrataManager::GetStrataDescription(const FName& Type) const
{
	return reinterpret_cast<FStrataDescription*>(StrataDescriptionDataTable->FindRowUnchecked(Type));
}

