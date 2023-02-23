#include "TimeControllerWidget.h"

#include "MyProject2/MyGameState.h"

void UTimeControllerWidget::BeginPlay()
{
	SpeedUpButton->OnClicked.AddDynamic(this, &UTimeControllerWidget::SpeedUpButtonOnClick);
	SlowDownButton->OnClicked.AddDynamic(this, &UTimeControllerWidget::SlowDownButtonOnClick);
	PauseButton->OnClicked.AddDynamic(this, &UTimeControllerWidget::PauseButtonOnClick);
}

void UTimeControllerWidget::SetTime(const FString& Time)
{
	TimeTextBlock->SetText(FText::FromString(Time));
}

void UTimeControllerWidget::SpeedUpButtonOnClick()
{
	UInGameTime* GameTime = GetWorld()->GetSubsystem<UInGameTime>();
	GameTime->SpeedUpTime();
	SpeedProgressBar->SetPercent(1.0 * GameTime->GetTimeSpeed() / GameTime->GetMaxTimeSpeed());
}

void UTimeControllerWidget::SlowDownButtonOnClick()
{
	UInGameTime* GameTime = GetWorld()->GetSubsystem<UInGameTime>();
	GameTime->SlowDownTime();
	SpeedProgressBar->SetPercent(1.0 * GameTime->GetTimeSpeed() / GameTime->GetMaxTimeSpeed());
}

void UTimeControllerWidget::PauseButtonOnClick()
{
	UInGameTime* GameTime = GetWorld()->GetSubsystem<UInGameTime>();
	GameTime->SwitchPauseFlag();
}