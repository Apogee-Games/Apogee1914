#include "LevelsOverides/CountrySelection/CountrySelectionLevelGameMode.h"

#include "Characters/HUDs/CountrySelectionHUD.h"
#include "Characters/Pawns/CountrySelectionPawn.h"

ACountrySelectionLevelGameMode::ACountrySelectionLevelGameMode()
{
	DefaultPawnClass = ACountrySelectionPawn::StaticClass();
	HUDClass = ACountrySelectionHUD::StaticClass();
}

void ACountrySelectionLevelGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);

	NewPlayer->SetInputMode(InputMode);
	NewPlayer->SetShowMouseCursor(true);
}
