#pragma once
#include "Scenario.h"
#include "Administration/Instances/State.h"

#include "StateManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UStateManager: public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	UState* GetState(UStateDescription* StateDescription) const;
	
	bool AreProvincesInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const;
	
	bool AreProvincesNotInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;
	
	bool AreProvincesNotInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const;

	virtual ELoadStage GetLoadStage() override;
private:
	UPROPERTY()
	TMap<UStateDescription*, UState*> StateMap;

	void Clear();

	void Init(UScenario* Scenario);
};
