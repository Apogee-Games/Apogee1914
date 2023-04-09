// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/Task.h"

#include "MyGameInstance.h"
#include "Characters/AIPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"

EBTNodeResult::Type UTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) != EBTNodeResult::Succeeded)
	{
		return EBTNodeResult::Failed;
	}
	/*
	UMyGameInstance* GameInstance = GetWorld()->GetGameInstance<UMyGameInstance>();

	
	UBoxesMap* BoxesMap = GameInstance->GetSubsystem<UBoxesMap>();
	UProvincesMap* ProvincesMap = GameInstance->GetSubsystem<UProvincesMap>();
	UProvinceManager* ProvinceManager = GameInstance->GetSubsystem<UProvinceManager>();
	UUnitsFactory* Factory = GameInstance->GetSubsystem<UUnitsFactory>();

	
	const TMap<FColor, TSet<FColor>>& Neigbours = ProvincesMap->GetNeighbours();

	for (const auto& Box: BoxesMap->GetBoxes())
	{
		if (Box->GetCountry() == Country)
		{
			for (const auto& Province: Box->GetProvinces())
			{
				if (Province->GetUnits().Num() < 3)
				{
					bool IsBorderProvince = false;
					for (const auto& Neighbour: Neigbours[Province->GetId()])
					{
						UProvince* NeighbourProvince = ProvinceManager->GetProvince(Neighbour);
						if (NeighbourProvince && NeighbourProvince->GetCountryController() != Province->GetCountryController())
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
	*/
	
	return EBTNodeResult::Succeeded;
}
