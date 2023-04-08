// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/AdvanceTroopsTask.h"

#include "MyGameInstance.h"

EBTNodeResult::Type UAdvanceTroopsTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) != EBTNodeResult::Succeeded)
	{
		return EBTNodeResult::Failed;
	}
	
	UMyGameInstance* GameInstance = GetWorld()->GetGameInstance<UMyGameInstance>();
	UProvincesMap* ProvincesMap = GameInstance->GetSubsystem<UProvincesMap>();
	UProvinceManager* ProvinceManager = GameInstance->GetSubsystem<UProvinceManager>();
	UUnitsMover* UnitsMover = GameInstance->GetSubsystem<UUnitsMover>();
	
	const TMap<FColor, TSet<FColor>>& Neigbours = ProvincesMap->GetNeighbours();

	TArray<UUnit*> MovableUnits;
	TArray<UProvince*> Provinces;
	
	for (const auto& Province: Country->GetProvinces())
	{
		TArray<UUnit*> Units = Province->GetUnits();

		if (Units.IsEmpty()) continue;
		
		bool HasEnemyNeighbour = false;
		
		for (const auto& NeighbourColor: Neigbours[Province->GetId()])
		{
			UProvince* NeighbourProvince = ProvinceManager->GetProvince(NeighbourColor);
			if (NeighbourProvince && NeighbourProvince->GetCountryController()->IsInWarWith(Country))
			{
				HasEnemyNeighbour = true;
				Provinces.Add(NeighbourProvince);
			} 
		}

		if (HasEnemyNeighbour)
		{
			for (const auto& Unit: Units)
			{
				MovableUnits.Add(Unit);
			}
		}
	}

	if (MovableUnits.IsEmpty() || Provinces.IsEmpty()) return EBTNodeResult::Succeeded;
	
	if (MovableUnits.Num() > Provinces.Num())
	{
		int Size = MovableUnits.Num() / Provinces.Num();
		for (int i = 0; i < Provinces.Num(); ++i)
		{
			for (int j = 0; j < Size && i * Size + j < MovableUnits.Num(); ++j)
			{
				UnitsMover->MoveUnit(MovableUnits[i * Size + j], Provinces[i]);
			}
		}
		for (int i = Provinces.Num() * Size; i < MovableUnits.Num(); ++i)
		{
			UnitsMover->MoveUnit(MovableUnits[i], Provinces[0]);
		}
	} else
	{
		for (int i = 0; i < MovableUnits.Num(); ++i)
		{
			UnitsMover->MoveUnit(MovableUnits[i], Provinces[i]);
		}
	}
	

	return EBTNodeResult::Succeeded;
}
