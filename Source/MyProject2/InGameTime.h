#pragma once

class FInGameTime
{

public:
	FInGameTime(FDateTime* CurrentTime, int MaxTimeSpeed);

	int GetTimeSpeed() const;

	int GetMaxTimeSpeed() const;
	
	void SpeedUpTime();

	void SlowDownTime();

	bool IsGamePaused() const;

	void PauseGame();

	void ResumeGame();

	void SwitchPauseFlag();
	
	FDateTime* GetTime() const;

	void UpdateCurrentTime(float DeltaSeconds);

private:
	
	FDateTime* CurrentTime;

	bool bIsGamePaused = true;
	
	int TimeSpeed = 1;

	int MaxTimeSpeed;
};
