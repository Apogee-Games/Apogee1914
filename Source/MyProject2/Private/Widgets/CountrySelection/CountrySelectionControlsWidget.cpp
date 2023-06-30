#include "Widgets/CountrySelection/CountrySelectionControlsWidget.h"

#include "MyGameInstance.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void UCountrySelectionControlsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayButton->OnClicked.AddDynamic(this, &UCountrySelectionControlsWidget::OnPlayButtonClick);
	BackButton->OnClicked.AddDynamic(this, &UCountrySelectionControlsWidget::OnBackButtonClick);

	PlayButton->SetIsEnabled(false);
	
	GetGameInstance<UMyGameInstance>()->OnCountrySelected.AddUObject(this, &UCountrySelectionControlsWidget::CountryWasSelected);
}

void UCountrySelectionControlsWidget::CountryWasSelected(int32 PlayerId, UCountry* Country)
{
	int32 OwnerPlayerId = GetTypeHash(GetOwningPlayer()->GetPlayerState<APlayerState>()->GetUniqueId());
	if (OwnerPlayerId == PlayerId) {
		PlayButton->SetIsEnabled(Country != nullptr);
	}
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
