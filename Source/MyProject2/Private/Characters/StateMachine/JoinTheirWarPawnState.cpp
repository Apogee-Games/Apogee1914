#include "Characters/StateMachine/JoinTheirWarPawnState.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Diplomacy/Wars/Join/TheirWar/TheirWarsListWidget.h"

TSharedPtr<FPawnState> FJoinTheirWarPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FJoinTheirWarPawnState>(new FJoinTheirWarPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FJoinTheirWarPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FJoinTheirWarPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

bool FJoinTheirWarPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UTheirWarsListWidget*>(Widget) != nullptr;
}

bool FJoinTheirWarPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FJoinTheirWarPawnState::FJoinTheirWarPawnState()
{
}

