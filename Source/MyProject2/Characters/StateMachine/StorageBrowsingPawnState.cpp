#include "StorageBrowsingPawnState.h"

#include "NoActionPawnState.h"
#include "MyProject2/Widgets/Economics/StorageGoodsListWidget.h"


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
	return FNoActionPawnState::GetInstance()->LeftClick(Pawn);
}

TSharedPtr<FPawnState> FStorageBrowsingPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	return FNoActionPawnState::GetInstance()->RightClick(Pawn);
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
