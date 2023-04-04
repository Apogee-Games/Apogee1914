#include "Economics/Managers/GoodsManager.h"

#include "MyGameInstance.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

bool UGoodsManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UGoodsManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GoodsDescriptions = GetWorld()->GetGameInstance<UMyGameInstance>()->ActiveScenario->GoodsDescriptions;
}

UGoodDescription* UGoodsManager::GetGoodDescription(const FName& GoodName) const
{
	return GoodsDescriptions[GoodName];
}
