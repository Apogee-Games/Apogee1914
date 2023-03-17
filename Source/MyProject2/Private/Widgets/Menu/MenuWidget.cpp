#include "Widgets/Menu/MenuWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ResumeButton->OnClicked.AddDynamic(this, &UMenuWidget::OnResumeButtonClick);
	MainMenuButton->OnClicked.AddDynamic(this, &UMenuWidget::OnMainMenuButtonClick);
	ExitGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnExitGameButtonClick);
}

void UMenuWidget::OnResumeButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->UnPause();
}

void UMenuWidget::OnMainMenuButtonClick()
{
	// TODO: Add save notification
	UGameplayStatics::OpenLevel(this, TEXT("MainMenu"));
}

void UMenuWidget::OnExitGameButtonClick()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
