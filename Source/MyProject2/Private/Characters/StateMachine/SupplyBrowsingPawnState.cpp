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

TSharedPtr<FPawnState> FSupplyBrowsingPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FSupplyBrowsingPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);
}

bool FSupplyBrowsingPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UUnitsSupplyListWidget*>(Widget) != nullptr;
}

bool FSupplyBrowsingPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FSupplyBrowsingPawnState::FSupplyBrowsingPawnState()
{
}

