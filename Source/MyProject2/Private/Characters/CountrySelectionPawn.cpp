#include "Characters/CountrySelectionPawn.h"

void ACountrySelectionPawn::BeginPlay()
{
	Super::BeginPlay();
	if (CountrySelectionWidgetClass)
	{
		CountrySelectionWidget = CreateWidget<UCountrySelectionWidget>(GetController<APlayerController>(), CountrySelectionWidgetClass);
		if (CountrySelectionWidget)
		{
			CountrySelectionWidget->AddToPlayerScreen();
		}
	}
}

void ACountrySelectionPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CountrySelectionWidget)
	{
		CountrySelectionWidget->RemoveFromParent();
	}
	Super::EndPlay(EndPlayReason);
}
