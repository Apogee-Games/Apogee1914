#include "Widgets/TimeControllerWidget.h"
#include "InGameTime.h"


void UTimeControllerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SpeedUpButton->OnClicked.AddDynamic(this, &UTimeControllerWidget::SpeedUpButtonOnClick);
	SlowDownButton->OnClicked.AddDynamic(this, &UTimeControllerWidget::SlowDownButtonOnClick);
	PauseButton->OnClicked.AddDynamic(this, &UTimeControllerWidget::PauseButtonOnClick);

	TimeToolTipWidget = CreateWidget<UToolTipWidget>(this, ToolTipWidgetClass);
	SetToolTip(TimeToolTipWidget);
	
	SetTime(GetGameInstance()->GetSubsystem<UInGameTime>()->GetStringTime());
}

void UTimeControllerWidget::SetTime(const FText& Time)
{
	TimeTextBlock->SetText(Time);
	TimeToolTipWidget->SetData(Time);
}

void UTimeControllerWidget::SetSpeedPercentage(float NewSpeedPercentage)
{
	SpeedProgressBar->SetPercent(NewSpeedPercentage);
}

void UTimeControllerWidget::SpeedUpButtonOnClick()
{
	GetGameInstance()->GetSubsystem<UInGameTime>()->SpeedUpTime();
}

void UTimeControllerWidget::SlowDownButtonOnClick()
{
	GetGameInstance()->GetSubsystem<UInGameTime>()->SlowDownTime();
}

void UTimeControllerWidget::PauseButtonOnClick()
{
	GetGameInstance()->GetSubsystem<UInGameTime>()->SwitchPauseFlag();
}
