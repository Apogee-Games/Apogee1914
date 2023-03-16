#include "Widgets/MainMenu/MainMenuWidget.h"

#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SinglePlayerButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSinglePlayerButtonClick);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButtonClick);
}

void UMainMenuWidget::OnSinglePlayerButtonClick()
{
	UGameplayStatics::OpenLevel(this, TEXT("CountrySelection"));
}

void UMainMenuWidget::OnExitButtonClick()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);;
}
