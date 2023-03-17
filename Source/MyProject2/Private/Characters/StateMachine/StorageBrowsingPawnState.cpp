#include "Characters/StateMachine/StorageBrowsingPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Economics/Storage/StorageGoodsListWidget.h"


TSharedPtr<FPawnState> FStorageBrowsingPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FStorageBrowsingPawnState>(new FStorageBrowsingPawnState);
	}
	return Instance;
}


TSharedPtr<FPawnState> FStorageBrowsingPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FStorageBrowsingPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);
}

bool FStorageBrowsingPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UStorageGoodsListWidget*>(Widget) != nullptr;
}

bool FStorageBrowsingPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FStorageBrowsingPawnState::FStorageBrowsingPawnState()
{
}
