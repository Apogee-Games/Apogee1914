#include "Characters/StateMachine/CountryManagementPawnState.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Administration/Country/CountryManagementWidget.h"

TSharedPtr<FPawnState> FCountryManagementPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedRef<FCountryManagementPawnState>(new FCountryManagementPawnState);
	}

	return Instance;
}

TSharedPtr<FPawnState> FCountryManagementPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FCountryManagementPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);
}

bool FCountryManagementPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UCountryManagementWidget*>(Widget) != nullptr;
}

bool FCountryManagementPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FCountryManagementPawnState::FCountryManagementPawnState()
{
}
