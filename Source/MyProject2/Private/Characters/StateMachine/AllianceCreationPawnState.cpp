#include "Characters/StateMachine/AllianceCreationPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Characters/StateMachine/PawnState.h"
#include "Widgets/Diplomacy/Alliance/Creation/AllianceCreationWidget.h"

TSharedPtr<FPawnState> FAllianceCreationPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FAllianceCreationPawnState>(new FAllianceCreationPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FAllianceCreationPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FAllianceCreationPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);
}

bool FAllianceCreationPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UAllianceCreationWidget*>(Widget) != nullptr;
}

bool FAllianceCreationPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FAllianceCreationPawnState::FAllianceCreationPawnState()
{
}
