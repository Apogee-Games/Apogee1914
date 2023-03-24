#include "Characters/StateMachine/LawsBrowsingPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Administration/Laws/LawsGroupWidget.h"
#include "Widgets/Administration/Laws/LawsWidget.h"

TSharedPtr<FPawnState> FLawsBrowsingPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FLawsBrowsingPawnState>(new FLawsBrowsingPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FLawsBrowsingPawnState::LeftClick(APawn* ProvidedPawn)
{
	return Instance;
}

TSharedPtr<FPawnState> FLawsBrowsingPawnState::RightClick(APawn* ProvidedPawn)
{
	return Instance;
}

bool FLawsBrowsingPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<ULawsWidget*>(Widget) != nullptr;
}

bool FLawsBrowsingPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FLawsBrowsingPawnState::FLawsBrowsingPawnState()
{
	
}
