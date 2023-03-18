#include "Economics/Managers/GoodManager.h"

#include "MyGameInstance.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

bool UGoodManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UGoodManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GoodDescriptionDataTable = GetWorld()->GetGameInstance<UMyGameInstance>()->ActiveScenario->GoodDescriptionDataTable;
}

FGoodDescription* UGoodManager::GetGoodDescription(const FString& GoodName) const
{
	return reinterpret_cast<FGoodDescription*>(GoodDescriptionDataTable->FindRowUnchecked(FName(GoodName)));
}
