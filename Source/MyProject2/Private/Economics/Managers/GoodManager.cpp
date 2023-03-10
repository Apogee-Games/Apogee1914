#include "Economics/Managers/GoodManager.h"

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
