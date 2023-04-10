// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Characters/AIPlayerController.h"
#include "Characters/AIPlayerPawn.h"
#include "UObject/Object.h"
#include "BaseTask.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UBaseTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	AAIPlayerController* Controller;

	UPROPERTY()
	AAIPlayerPawn* Pawn;

	UPROPERTY()
	UCountry* Country;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
