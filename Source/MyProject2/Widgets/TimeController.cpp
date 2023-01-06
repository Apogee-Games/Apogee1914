#include "TimeController.h"

#include "MyProject2/MyGameState.h"

void UTimeController::BeginPlay()
{
	SpeedUpButton->OnClicked.AddDynamic(this, &UTimeController::SpeedUpButtonOnClick);
	SlowDownButton->OnClicked.AddDynamic(this, &UTimeController::SlowDownButtonOnClick);
	PauseButton->OnClicked.AddDynamic(this, &UTimeController::PauseButtonOnClick);
	SpeedProgressBar->SetPercent(0.1);
}

void UTimeController::SetTime(const FString& Time)
{
	TimeTextBlock->SetText(FText::FromString(Time));
}

void UTimeController::SpeedUpButtonOnClick()
{
	AMyGameState* GameState = Cast<AMyGameState>(GetWorld()->GetGameState());
	GameState->SpeedUpTime();
	if (SpeedProgressBar->Percent <= 0.91) {
		SpeedProgressBar->SetPercent(SpeedProgressBar->Percent + 0.1);
	}
}

void UTimeController::SlowDownButtonOnClick()
{
	AMyGameState* GameState = Cast<AMyGameState>(GetWorld()->GetGameState());
	GameState->SlowDownTime();
	if (SpeedProgressBar->Percent > 0.11) {
		SpeedProgressBar->SetPercent(SpeedProgressBar->Percent - 0.1);
	}
}

void UTimeController::PauseButtonOnClick()
{
	AMyGameState* GameState = Cast<AMyGameState>(GetWorld()->GetGameState());
	GameState->SwitchPauseFlag();
}
