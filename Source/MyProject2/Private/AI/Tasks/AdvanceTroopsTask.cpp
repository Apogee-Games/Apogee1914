// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/AdvanceTroopsTask.h"

#include "MyGameInstance.h"
#include "Maps/MapsDataGatherer.h"

EBTNodeResult::Type UAdvanceTroopsTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) != EBTNodeResult::Succeeded)
	{
		return EBTNodeResult::Failed;
	}
	
	UMyGameInstance* GameInstance = GetWorld()->GetGameInstance<UMyGameInstance>();
	UUnitsMover* UnitsMover = GameInstance->GetSubsystem<UUnitsMover>();
	
	const TMap<UProvince*, TSet<UProvince*>>& Neigbours = GameInstance->GetSubsystem<UMapsDataGatherer>()->GetNeighbourProvinces();

	TArray<UUnit*> MovableUnits;
	TArray<UProvince*> Provinces;
	
	for (const auto& Province: Country->GetProvinces())
	{
		for (const auto& Neighbour: Neigbours[Province])
		{
			if (Neighbour && Neighbour->GetCountryController()->IsInWarWith(Country))
			{
				Provinces.Add(Neighbour);
			} 
		}
		
		TArray<UUnit*> Units = Province->GetUnits();

		if (Units.IsEmpty()) continue;

		for (const auto& Unit: Units)
		{
			if (Unit->GetManpower())
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
