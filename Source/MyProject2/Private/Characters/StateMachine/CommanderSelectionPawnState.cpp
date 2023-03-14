#include "Characters/StateMachine/CommanderSelectionPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Military/Commanders/CommanderListWidget.h"

TSharedPtr<FPawnState> FCommanderSelectionPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FCommanderSelectionPawnState>(new FCommanderSelectionPawnState());
	}
	return Instance;
}

TSharedPtr<FPawnState> FCommanderSelectionPawnState::LeftClick(AHumanPlayerPawn* Pawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(Pawn);
}

TSharedPtr<FPawnState> FCommanderSelectionPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(Pawn);
}

bool FCommanderSelectionPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UCommanderListWidget*>(Widget) != nullptr;
}

bool FCommanderSelectionPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FCommanderSelectionPawnState::FCommanderSelectionPawnState()
{
}
