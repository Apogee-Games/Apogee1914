#pragma once
#include "Widgets/TimeController.h"
#include "InGameTime.generated.h"

UCLASS()
class UInGameTime: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void Deinitialize() override;
	
	virtual void Tick(float DeltaTime);
	
	int GetTimeSpeed() const;

	int GetMaxTimeSpeed() const;

	void SpeedUpTime();

	void SlowDownTime();

	bool IsGamePaused() const;

	void PauseGame();

	void ResumeGame();

	void SwitchPauseFlag();

	const FDateTime& GetTime() const;

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
	
	float_t SpeedMultiplier;

	int32 MaxTimeSpeed;
	
	bool bIsGamePaused = true;

	int32 TimeSpeed = 1;
	
	int32 TotalObjectNumber = 1;

	UPROPERTY()
	UTimeController* TimeControllerWidget;

	void UpdateCurrentTime(const FTimespan& DeltaTimeSpan);

	void CheckDeltas(const FTimespan& DeltaTimeSpan);

	void RefreshWidget();
};

template <class T>
void UInGameTime::RegisterListener(T* Object, void(T::* Function)(), FTimespan Delta)
{
	RegisterListener(static_cast<UObject*>(Object), static_cast<void (UObject::*)()>(Function), Delta);
}
