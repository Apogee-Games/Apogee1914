#include "Characters/Pawns/MainMenuPawn.h"

#include "MyGameInstance.h"

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
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMainMenuPawn::InitializeGame, 1.0f);
}

void AMainMenuPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
	}
}

void AMainMenuPawn::InitializeGame()
{
	GetGameInstance<UMyGameInstance>()->OnStageLoadFinished.AddUObject(MainMenuWidget, &UMainMenuWidget::OnLoadStage);
	GetGameInstance<UMyGameInstance>()->InitializeActiveScenario();
}
