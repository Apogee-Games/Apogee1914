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

TSharedPtr<FPawnState> FCommanderSelectionPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FCommanderSelectionPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);
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
