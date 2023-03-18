#include "Characters/HUDs/CountrySelectionHUD.h"

void ACountrySelectionHUD::BeginPlay()
{
	Super::BeginPlay();
	if (ScenarioSelectionWidgetClass)
	{
		ScenarioSelectionWidget = CreateWidget<UScenarioSelectionWidget>(GetOwningPlayerController(), ScenarioSelectionWidgetClass);
		if (ScenarioSelectionWidget)
		{
			ScenarioSelectionWidget->AddToPlayerScreen();
		}
	}
	if (SelectedCountryWidgetClass)
	{
		SelectedCountryWidget = CreateWidget<USelectedCountryWidget>(GetOwningPlayerController(), SelectedCountryWidgetClass);
		if (SelectedCountryWidget)
		{
			SelectedCountryWidget->AddToPlayerScreen();
		}
	}
	if (CountrySelectionControlsWidgetClass)
	{
		CountrySelectionControlsWidget = CreateWidget<UCountrySelectionControlsWidget>(GetOwningPlayerController(), CountrySelectionControlsWidgetClass);
		if (CountrySelectionControlsWidget)
		{
			CountrySelectionControlsWidget->AddToPlayerScreen();
		}
	}
}

UScenarioSelectionWidget* ACountrySelectionHUD::GetScenarioSelectionWidget() const
{
	return ScenarioSelectionWidget;
}

USelectedCountryWidget* ACountrySelectionHUD::GetSelectedCountryWidget() const
{
	return SelectedCountryWidget;
}

UCountrySelectionControlsWidget* ACountrySelectionHUD::GetCountrySelectionControlsWidget() const
{
	return CountrySelectionControlsWidget;
}

void ACountrySelectionHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ScenarioSelectionWidget)
	{
		ScenarioSelectionWidget->RemoveFromParent();
	}
	if (SelectedCountryWidget)
	{
		SelectedCountryWidget->RemoveFromParent();
	}
	if (CountrySelectionControlsWidget)
	{
		CountrySelectionControlsWidget->RemoveFromParent();
	}
	Super::EndPlay(EndPlayReason);
}
