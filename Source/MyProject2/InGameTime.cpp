#include "InGameTime.h"

#include "MyGameState.h"

void UInGameTime::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	AMyGameState* GameState = GetWorld()->GetGameState<AMyGameState>();
	
	CurrentTime = GameState->StartTime; 
	MaxTimeSpeed = GameState->MaxTimeSpeed;
	SpeedMultiplier = GameState->SpeedMultiplier;
	
	TimeControllerWidget = CreateWidget<UTimeController>(GetWorld(), GameState->TimeControllerClass);
	TimeControllerWidget->BeginPlay();
	TimeControllerWidget->AddToViewport();
}

void UInGameTime::Deinitialize()
{
	Super::Deinitialize();
	if (TimeControllerWidget)
	{
		TimeControllerWidget->RemoveFromRoot();
	}
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
	RefreshWidget();
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

void UInGameTime::RefreshWidget()
{
	if (TimeControllerWidget)
	{
		const FString Time = CurrentTime.ToString(TEXT("%Y-%m-%d %H"));
		TimeControllerWidget->SetTime(Time);
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
}

void UInGameTime::SlowDownTime()
{
	if (TimeSpeed <= 1) return;
	--TimeSpeed;
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
