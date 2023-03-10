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


TSharedPtr<FPawnState> FStorageBrowsingPawnState::LeftClick(AHumanPlayerPawn* Pawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(Pawn);
}

TSharedPtr<FPawnState> FStorageBrowsingPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(Pawn);
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
