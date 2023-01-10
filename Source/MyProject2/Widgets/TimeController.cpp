#include "TimeController.h"

#include "MyProject2/MyGameState.h"

void UTimeController::BeginPlay()
{
	SpeedUpButton->OnClicked.AddDynamic(this, &UTimeController::SpeedUpButtonOnClick);
	SlowDownButton->OnClicked.AddDynamic(this, &UTimeController::SlowDownButtonOnClick);
	PauseButton->OnClicked.AddDynamic(this, &UTimeController::PauseButtonOnClick);
}

void UTimeController::SetTime(const FString& Time)
{
	TimeTextBlock->SetText(FText::FromString(Time));
}

void UTimeController::SpeedUpButtonOnClick()
{
	FInGameTime* GameTime = Cast<AMyGameState>(GetWorld()->GetGameState())->GetInGameTime();
	GameTime->SpeedUpTime();
	SpeedProgressBar->SetPercent(1.0 * GameTime->GetTimeSpeed() / GameTime->GetMaxTimeSpeed());
}

void UTimeController::SlowDownButtonOnClick()
{
	FInGameTime* GameTime = Cast<AMyGameState>(GetWorld()->GetGameState())->GetInGameTime();
	GameTime->SlowDownTime();
	SpeedProgressBar->SetPercent(1.0 * GameTime->GetTimeSpeed() / GameTime->GetMaxTimeSpeed());
}

void UTimeController::PauseButtonOnClick()
{
	FInGameTime* GameTime = Cast<AMyGameState>(GetWorld()->GetGameState())->GetInGameTime();
	GameTime->SwitchPauseFlag();
}
