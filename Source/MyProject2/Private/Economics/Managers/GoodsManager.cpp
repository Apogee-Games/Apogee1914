#include "Economics/Managers/GoodsManager.h"

#include "MyGameInstance.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

void UGoodsManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

UGoodDescription* UGoodsManager::GetGoodDescription(const FName& GoodName) const
{
	return GoodsDescriptions[GoodName];
}

ELoadStage UGoodsManager::GetLoadStage()
{
	return ELoadStage::GoodsManager;
}

void UGoodsManager::Clear()
{
	GoodsDescriptions.Empty();
}

void UGoodsManager::Init(UScenario* Scenario)
{
	GoodsDescriptions = Scenario->GoodsDescriptions;
}
