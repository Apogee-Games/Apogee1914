#include "InGameTime.h"

#include "Characters/HumanPlayerHUD.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

bool UInGameTime::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UInGameTime::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CurrentTime = StartTime;
	RefreshWidgetDate();
	RefreshWidgetSpeed();
}

void UInGameTime::Tick(float DeltaTime)
{
	if (!IsGamePaused())
	{
		UpdateCurrentTime(DeltaTime * 1000);
	}
}

int32 UInGameTime::GetTimeSpeed() const
{
	return TimeSpeed;
}

int32 UInGameTime::GetMaxTimeSpeed() const
{
	return MaxTimeSpeed;
}

void UInGameTime::UpdateCurrentTime(const float DeltaSeconds)
{
	UpdateCurrentTime(FTimespan(0, DeltaSeconds * TimeSpeed * SpeedMultiplier, 0));
}

void UInGameTime::RegisterListener(UObject* Object, void (UObject::*Function)(), FTimespan Delta)
{
	Functions.Add(TotalObjectNumber, Function);
	CurrentDeltas.Add(TotalObjectNumber, Delta.GetTicks());
	Deltas.Add(TotalObjectNumber, Delta.GetTicks());
	Objects.Add(TotalObjectNumber, Object);
	++TotalObjectNumber;
}

void UInGameTime::UpdateCurrentTime(const FTimespan& DeltaTimeSpan)
{
	CurrentTime += DeltaTimeSpan;
	CheckDeltas(DeltaTimeSpan);
	RefreshWidgetDate();
}

void UInGameTime::CheckDeltas(const FTimespan& DeltaTimeSpan)
{
	for (auto& [Id, CurrentDelta] : CurrentDeltas)
	{
		CurrentDelta -= DeltaTimeSpan.GetTicks();
		if (CurrentDelta <= 0)
		{
			CurrentDelta = Deltas[Id];
			(Objects[Id]->*Functions[Id])();
		}
	}
}

void UInGameTime::RefreshWidgetDate()
{
	// TODO: Add logic for multiplayer
	UTimeControllerWidget* TimeControllerWidget = GetWorld()->GetFirstPlayerController()->GetHUD<AHumanPlayerHUD>()->GetTimeControllerWidget();
	if (TimeControllerWidget)
	{
		TimeControllerWidget->SetTime(CurrentTime.ToString(TEXT("%Y-%m-%d %H")));
	}
}

void UInGameTime::RefreshWidgetSpeed()
{
	// TODO: Add logic for multiplayer
	UTimeControllerWidget* TimeControllerWidget = GetWorld()->GetFirstPlayerController()->GetHUD<AHumanPlayerHUD>()->GetTimeControllerWidget();
	if (TimeControllerWidget)
	{
		TimeControllerWidget->SetSpeedPercentage(1.0 * TimeSpeed / MaxTimeSpeed);
	}
}

const FDateTime& UInGameTime::GetTime() const
{
	return CurrentTime;
}

void UInGameTime::SpeedUpTime()
{
	if (TimeSpeed >= MaxTimeSpeed) return;
	++TimeSpeed;
	RefreshWidgetSpeed();
}

void UInGameTime::SlowDownTime()
{
	if (TimeSpeed <= 1) return;
	--TimeSpeed;
	RefreshWidgetSpeed();
}

bool UInGameTime::IsGamePaused() const
{
	return bIsGamePaused;
}

void UInGameTime::PauseGame()
{
	bIsGamePaused = true;
}

void UInGameTime::ResumeGame()
{
	bIsGamePaused = false;
}

void UInGameTime::SwitchPauseFlag()
{
	bIsGamePaused = !bIsGamePaused;
}
