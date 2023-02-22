#pragma once
#include "MyProject2/Administration/Instances/State.h"

#include "StateManager.generated.h"

UCLASS()
class UStateManager: public UWorldSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UState* GetState(const FString& StateId) const;
	
	bool AreProvincesInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const;
	
	bool AreProvincesNotInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;
	
	bool AreProvincesNotInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const;

private:
	UPROPERTY()
	TMap<FString, UState*> StateMap;

	void InitStates(UDataTable* StatesDescriptions);
};
