// Fill out your copyright notice in the Description page of Project Settings.


#include "Military/Managers/BattlesManager.h"

#include "InGameTime.h"
#include "Military/Managers/UnitsFactory.h"
#include "Military/Managers/UnitsMover.h"

void UBattlesManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UBattlesManager::AddBattle(UProvince* Province)
{
	Provinces.Add(Province);
	UUnitsMover* UnitsMover = GetGameInstance()->GetSubsystem<UUnitsMover>();
	/*for (const auto& Unit: Province->GetAttackers())
	{
		UnitsMover->SuspendMovement(Unit);
	}*/
}

void UBattlesManager::Tick()
{
	UUnitsMover* UnitsMover = GetGameInstance()->GetSubsystem<UUnitsMover>();
	UUnitsFactory* UnitsFactory = GetGameInstance()->GetSubsystem<UUnitsFactory>();
	
	for (const auto& Province: Provinces)
	{
		TickBattle(Province, UnitsMover, UnitsFactory);
	}
	
	RemoveFinishedBattles();
}

ELoadStage UBattlesManager::GetLoadStage()
{
	return ELoadStage::BattlesManager;
}

void UBattlesManager::Clear()
{
	Provinces.Empty();
}

void UBattlesManager::Init(UScenario* Scenario)
{
	GetGameInstance()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UBattlesManager::Tick, BattleUpdateMidDelta);
}

void UBattlesManager::TickBattle(UProvince* Province, UUnitsMover* UnitsMover, UUnitsFactory* UnitsFactory)
{
	if (Province->GetAttackers().IsEmpty() || Province->GetDefenders().IsEmpty())
	{
		FinishedBattleProvinces.Enqueue(Province);
		return;
	}

	const float AttackerAttackScore = CalculateAttackScore(Province->GetAttackers());
	const float DefenderAttackScore = CalculateAttackScore(Province->GetDefenders());

	TQueue<UUnit*> UnitsToRemove;

	ApplyDamage(Province->GetAttackers(), DefenderAttackScore, UnitsToRemove, UnitsMover);
	ApplyDamage(Province->GetDefenders(), AttackerAttackScore, UnitsToRemove, UnitsMover);
		
	RemoveUnits(UnitsToRemove, UnitsFactory);
}

float UBattlesManager::CalculateAttackScore(const TArray<UUnit*>& Units)
{
	float Score = 0;
	for (const auto& Unit: Units)
	{
		Score += Unit->GetAttackScore();
	}
	return Score;
}

void UBattlesManager::ApplyDamage(const TArray<UUnit*>& Units, float AttackScore, TQueue<UUnit*>& UnitsToRemove, UUnitsMover* UnitsMover)
{
	for (const auto& Unit: Units)
	{
		AttackScore -= Unit->GetDefenceScore();
		AttackScore -= Unit->Damage(AttackScore);
		if (Unit->GetManpower() == 0.0)
		{
			if (!UnitsMover->Retreat(Unit))
			{
				UnitsToRemove.Enqueue(Unit);
			}
		}
	}
}

void UBattlesManager::RemoveUnits(TQueue<UUnit*>& UnitsToRemove, UUnitsFactory* UnitsFactory)
{
	UUnit* Unit;
	while (!UnitsToRemove.IsEmpty())
	{
		UnitsToRemove.Dequeue(Unit);
		UnitsFactory->RemoveUnit(Unit);
	}
}

void UBattlesManager::RemoveFinishedBattles()
{
	UProvince* Province;
	while (!FinishedBattleProvinces.IsEmpty())
	{
		FinishedBattleProvinces.Dequeue(Province);
		Provinces.Remove(Province);
		Province->UpdateControllerCountry();
	}
}
