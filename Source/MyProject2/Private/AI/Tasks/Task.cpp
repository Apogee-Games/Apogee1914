﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/Task.h"

#include "MyGameInstance.h"
#include "Characters/AIPlayerPawn.h"
#include "Maps/MapsDataGatherer.h"
#include "Military/Managers/UnitsFactory.h"

EBTNodeResult::Type UTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) != EBTNodeResult::Succeeded)
	{
		return EBTNodeResult::Failed;
	}

	UMyGameInstance* GameInstance = GetWorld()->GetGameInstance<UMyGameInstance>();

	UMapsDataGatherer* MapsDataGatherer = GameInstance->GetSubsystem<UMapsDataGatherer>();
	UUnitsFactory* Factory = GameInstance->GetSubsystem<UUnitsFactory>();

	
	const TMap<UProvince*, TSet<UProvince*>>& Neigbours = MapsDataGatherer->GetNeighbourProvinces();

	for (const auto& Box: MapsDataGatherer->GetBoxes())
	{
		if (Box->GetCountry() == Country)
		{
			for (const auto& Province: Box->GetProvinces())
			{
				if (Province->GetUnits().Num() < 3)
				{
					bool IsBorderProvince = false;
					for (const auto& Neighbour: Neigbours[Province])
					{
						if (Neighbour && Neighbour->GetCountryController() != Province->GetCountryController())
						{
							IsBorderProvince = true;
							break;
						}
					}
					if (IsBorderProvince) {
						Factory->CreateUnit(Factory->GetUnitsDescriptions()[0], Province);
					}
				}
			}
		}
	}
	
	return EBTNodeResult::Succeeded;
}
