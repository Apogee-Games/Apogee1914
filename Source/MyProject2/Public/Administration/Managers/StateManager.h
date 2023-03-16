#pragma once
#include "Administration/Instances/State.h"

#include "StateManager.generated.h"

UCLASS(Abstract, Blueprintable)
class UStateManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UState* GetState(const FName& StateId) const;
	
	bool AreProvincesInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;

	bool AreProvincesInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const;
	
	bool AreProvincesNotInTheSameState(const FColor& ProvinceAColor, const FColor& ProvinceBColor) const;
	
	bool AreProvincesNotInTheSameState(const UProvince* ProvinceA, const UProvince* ProvinceB) const;
private:
	UPROPERTY()
	TMap<FName, UState*> StateMap;

	void InitStates(UDataTable* StatesDescriptions);
};
