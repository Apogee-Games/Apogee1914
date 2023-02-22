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
	UInGameTime* GameTime = GetWorld()->GetSubsystem<UInGameTime>();
	GameTime->SpeedUpTime();
	SpeedProgressBar->SetPercent(1.0 * GameTime->GetTimeSpeed() / GameTime->GetMaxTimeSpeed());
}

void UTimeController::SlowDownButtonOnClick()
{
	UInGameTime* GameTime = GetWorld()->GetSubsystem<UInGameTime>();
	GameTime->SlowDownTime();
	SpeedProgressBar->SetPercent(1.0 * GameTime->GetTimeSpeed() / GameTime->GetMaxTimeSpeed());
}

void UTimeController::PauseButtonOnClick()
{
	UInGameTime* GameTime = GetWorld()->GetSubsystem<UInGameTime>();
	GameTime->SwitchPauseFlag();
}
