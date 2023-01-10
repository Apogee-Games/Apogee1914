#include "InGameTime.h"

FInGameTime::FInGameTime(FDateTime* CurrentTime, int MaxTimeSpeed):
	CurrentTime(CurrentTime), MaxTimeSpeed(MaxTimeSpeed)
{
}

int FInGameTime::GetTimeSpeed() const
{
	return TimeSpeed;
}

int FInGameTime::GetMaxTimeSpeed() const
{
	return MaxTimeSpeed;
}

void FInGameTime::UpdateCurrentTime(float DeltaSeconds)
{
	(*CurrentTime) += FTimespan(0, DeltaSeconds * TimeSpeed / 5, 0);
}

FDateTime* FInGameTime::GetTime() const
{
	return CurrentTime;
}


void FInGameTime::SpeedUpTime()
{
	if (TimeSpeed >= MaxTimeSpeed) return;
	++TimeSpeed;
}

void FInGameTime::SlowDownTime()
{
	if (TimeSpeed <= 1) return;
	--TimeSpeed;
}

bool FInGameTime::IsGamePaused() const
{
	return bIsGamePaused;
}

void FInGameTime::PauseGame()
{
	bIsGamePaused = true;
}

void FInGameTime::ResumeGame()
{
	bIsGamePaused = false;
}

void FInGameTime::SwitchPauseFlag()
{
	bIsGamePaused = !bIsGamePaused;
}
