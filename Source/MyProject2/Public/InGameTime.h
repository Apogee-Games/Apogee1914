#pragma once
#include "Scenario.h"
#include "Widgets/TimeControllerWidget.h"
#include "InGameTime.generated.h"

UCLASS(Abstract, Blueprintable)
class UInGameTime: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	virtual void Tick(float DeltaTime);
	
	int32 GetTimeSpeed() const;

	int32 GetMaxTimeSpeed() const;

	void SpeedUpTime();

	void SlowDownTime();

	bool IsGamePaused() const;

	void PauseGame();

	void ResumeGame();

	void SwitchPauseFlag();

	const FDateTime& GetTime() const;

	const FText GetStringTime() const;

	void UpdateCurrentTime(const float DeltaSeconds);

	template<class T>
	void RegisterListener(T* Object, void (T::*Function)(), FTimespan Delta);
	
	void RegisterListener(UObject* Object, void (UObject::*Function)(), FTimespan Delta);
private:
	TMap<int32, UObject*> Objects;

	TMap<int32, void(UObject::*)()> Functions;

	TMap<int32, int64> CurrentDeltas;

	TMap<int32, int64> Deltas;
	
	FDateTime CurrentTime;
	
	bool bIsGamePaused = true;

	int32 TimeSpeed = 1;
	
	int32 TotalObjectNumber = 1;

	int32 MaxTimeSpeed;

	float SpeedMultiplier;
	
	void Clear();

	void Init(UScenario* Scenario);
	
	void UpdateCurrentTime(const FTimespan& DeltaTimeSpan);

	void CheckDeltas(const FTimespan& DeltaTimeSpan);

	void RefreshWidgetDate();

	void RefreshWidgetSpeed();
};

template <class T>
void UInGameTime::RegisterListener(T* Object, void(T::* Function)(), FTimespan Delta)
{
	RegisterListener(static_cast<UObject*>(Object), static_cast<void (UObject::*)()>(Function), Delta);
}
