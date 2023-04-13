// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scenario.h"
#include "UnitsFactory.h"
#include "UnitsMover.h"
#include "Administration/Instances/Province.h"
#include "BattlesManager.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class MYPROJECT2_API UBattlesManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);

	void AddBattle(UProvince* Province);

	void Tick();

	UPROPERTY(EditDefaultsOnly)
	FTimespan BattleUpdateMidDelta = FTimespan(1, 0, 0);
	
private:
	UPROPERTY()
	TArray<UProvince*> Provinces;

	TQueue<UProvince*> FinishedBattleProvinces;
	
	void Clear();

	void Init(UScenario* Scenario);

	void TickBattle(UProvince* Province, UUnitsMover* UnitsMover, UUnitsFactory* UnitsFactory);
	
	float CalculateAttackScore(const TArray<UUnit*>& Units);

	void ApplyDamage(const TArray<UUnit*>& Units, float AttackScore, TQueue<UUnit*>& UnitsToRemove, UUnitsMover* UnitsMover);

	void RemoveUnits(TQueue<UUnit*>& UnitsToRemove, UUnitsFactory* UnitsFactory);

	void RemoveFinishedBattles();
};
