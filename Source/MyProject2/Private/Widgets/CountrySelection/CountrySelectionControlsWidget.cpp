#include "Widgets/CountrySelection/CountrySelectionControlsWidget.h"

#include "Kismet/GameplayStatics.h"

void UCountrySelectionControlsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayButton->OnClicked.AddDynamic(this, &UCountrySelectionControlsWidget::OnPlayButtonClick);
	BackButton->OnClicked.AddDynamic(this, &UCountrySelectionControlsWidget::OnBackButtonClick);
}

void UCountrySelectionControlsWidget::OnPlayButtonClick()
{
	UGameplayStatics::OpenLevel(this, TEXT("Game"));
}

void UCountrySelectionControlsWidget::OnBackButtonClick()
{
	// TODO: Add selected countries clearing in game instance
	UGameplayStatics::OpenLevel(this, TEXT("MainMenu"));
}
