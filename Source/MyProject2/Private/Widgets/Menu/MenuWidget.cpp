#include "Widgets/Menu/MenuWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UMenuWidget::OnResumeButtonClick);
	MainMenuButton->OnClicked.AddDynamic(this, &UMenuWidget::OnMainMenuButtonClick);
	ExitGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnExitGameButtonClick);
}

void UMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	ResumeButton->OnClicked.RemoveAll(this);
	MainMenuButton->OnClicked.RemoveAll(this);
	ExitGameButton->OnClicked.RemoveAll(this);
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
