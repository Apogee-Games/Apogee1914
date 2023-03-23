#include "Widgets/TimeControllerWidget.h"
#include "InGameTime.h"


void UTimeControllerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SpeedUpButton->OnClicked.AddDynamic(this, &UTimeControllerWidget::SpeedUpButtonOnClick);
	SlowDownButton->OnClicked.AddDynamic(this, &UTimeControllerWidget::SlowDownButtonOnClick);
	PauseButton->OnClicked.AddDynamic(this, &UTimeControllerWidget::PauseButtonOnClick);
}

void UTimeControllerWidget::SetTime(const FString& Time)
{
	TimeTextBlock->SetText(FText::FromString(Time));
}

void UTimeControllerWidget::SetSpeedPercentage(float NewSpeedPercentage)
{
	SpeedProgressBar->SetPercent(NewSpeedPercentage);
}

void UTimeControllerWidget::SpeedUpButtonOnClick()
{
	GetWorld()->GetSubsystem<UInGameTime>()->SpeedUpTime();
}

void UTimeControllerWidget::SlowDownButtonOnClick()
{
	GetWorld()->GetSubsystem<UInGameTime>()->SlowDownTime();
}

void UTimeControllerWidget::PauseButtonOnClick()
{
	GetWorld()->GetSubsystem<UInGameTime>()->SwitchPauseFlag();
}
