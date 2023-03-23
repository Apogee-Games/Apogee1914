#include "Characters/StateMachine/WarDescriptionBrowsingPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Diplomacy/Wars/Description/WarDescriptionWidget.h"

TSharedPtr<FPawnState> FWarDescriptionBrowsingPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FWarDescriptionBrowsingPawnState>(new FWarDescriptionBrowsingPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FWarDescriptionBrowsingPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FWarDescriptionBrowsingPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);
}

bool FWarDescriptionBrowsingPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UWarDescriptionWidget*>(Widget) != nullptr;
}

bool FWarDescriptionBrowsingPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FWarDescriptionBrowsingPawnState::FWarDescriptionBrowsingPawnState()
{
}
