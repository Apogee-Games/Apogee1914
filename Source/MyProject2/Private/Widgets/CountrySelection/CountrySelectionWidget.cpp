
#include "Widgets/CountrySelection/CountrySelectionWidget.h"

#include "MyGameInstance.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void UCountrySelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SaveButton->OnClicked.AddDynamic(this, &UCountrySelectionWidget::OnSaveButtonClick);
}

void UCountrySelectionWidget::OnSaveButtonClick()
{
	GetGameInstance<UMyGameInstance>()->SetRuledCountry(GetTypeHash(GetOwningPlayer()->GetPlayerState<APlayerState>()->GetUniqueId()), *CountryTagTextBox->GetText().ToString());
	UGameplayStatics::OpenLevel(this, TEXT("Game"));
}
