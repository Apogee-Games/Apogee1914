#include "Characters/Pawns/MainMenuPawn.h"

void AMainMenuPawn::BeginPlay()
{
	Super::BeginPlay();
	if (MainMenuWidgetClass) {
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetController<APlayerController>(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToPlayerScreen();
		}
	}
}

void AMainMenuPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
	}
}
