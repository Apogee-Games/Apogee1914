#include "Characters/StateMachine/SupplyBrowsingPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Economics/Storage/StorageGoodsListWidget.h"
#include "Widgets/Military/Supply/UnitsSupplyListWidget.h"


TSharedPtr<FPawnState> FSupplyBrowsingPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FSupplyBrowsingPawnState>(new FSupplyBrowsingPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FSupplyBrowsingPawnState::LeftClick(AHumanPlayerPawn* Pawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(Pawn);
}

TSharedPtr<FPawnState> FSupplyBrowsingPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(Pawn);
}

bool FSupplyBrowsingPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UUnitsSupplyListWidget*>(Widget) != nullptr;
}

bool FSupplyBrowsingPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UStorageGoodsListWidget*>(Widget) != nullptr;
}

FSupplyBrowsingPawnState::FSupplyBrowsingPawnState()
{
}

