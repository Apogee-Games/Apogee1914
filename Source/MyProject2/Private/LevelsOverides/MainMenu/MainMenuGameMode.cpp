#include "LevelsOverides/MainMenu/MainMenuGameMode.h"

#include "MyGameInstance.h"
#include "Characters/Pawns/MainMenuPawn.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	DefaultPawnClass = AMainMenuPawn::StaticClass();
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMainMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	FInputModeUIOnly InputMode;
	NewPlayer->SetInputMode(InputMode);
	NewPlayer->SetShowMouseCursor(true);
}
