#include "Economics/Managers/GoodManager.h"

#include "LevelsOverides/Game/GameLevelGameState.h"

bool UGoodManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UGoodManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GoodDescriptionDataTable
			= LoadObject<UDataTable>(nullptr,TEXT("/Game/Sources/goods_description"));
	
}

FGoodDescription* UGoodManager::GetGoodDescription(const FString& GoodName) const
{
	return reinterpret_cast<FGoodDescription*>(
		GoodDescriptionDataTable->FindRowUnchecked(FName(GoodName))
		);
}
