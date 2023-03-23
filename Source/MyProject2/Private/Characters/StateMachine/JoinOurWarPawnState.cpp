#include "Characters/StateMachine/JoinOurWarPawnState.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Diplomacy/Wars/Join/OurWar/OurWarsListWidget.h"
#include "Widgets/Diplomacy/Wars/Join/TheirWar/TheirWarsListWidget.h"

TSharedPtr<FPawnState> FJoinOurWarPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FJoinOurWarPawnState>(new FJoinOurWarPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FJoinOurWarPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FJoinOurWarPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

bool FJoinOurWarPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UOurWarsListWidget*>(Widget) != nullptr;
}

bool FJoinOurWarPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FJoinOurWarPawnState::FJoinOurWarPawnState()
{
}

