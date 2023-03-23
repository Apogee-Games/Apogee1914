#pragma once
#include "Scenario.h"
#include "Administration/Instances/State.h"

#include "StateManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UStateManager: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	UState* GetState(const FName& StateId) const;
	
	bool AreProvincesInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const;
	
	bool AreProvincesNotInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;
	
	bool AreProvincesNotInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const;
private:
	UPROPERTY()
	TMap<FName, UState*> StateMap;

	void Clear();

	void Init(UScenario* Scenario);
};
