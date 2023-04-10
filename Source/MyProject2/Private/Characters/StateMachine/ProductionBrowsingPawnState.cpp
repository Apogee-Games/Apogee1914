

#include "Characters/StateMachine/ProductionBrowsingPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Economics/Buildings/Production/ProductionListWidget.h"

TSharedPtr<FPawnState> FProductionBrowsingPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FProductionBrowsingPawnState>(new FProductionBrowsingPawnState);
	}
	return Instance;
}


TSharedPtr<FPawnState> FProductionBrowsingPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FProductionBrowsingPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);
}

bool FProductionBrowsingPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UProductionListWidget*>(Widget) != nullptr;
}

bool FProductionBrowsingPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FProductionBrowsingPawnState::FProductionBrowsingPawnState()
{
}
