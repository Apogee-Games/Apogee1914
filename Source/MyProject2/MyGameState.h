// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGameTime.h"
#include "GameFramework/GameStateBase.h"
#include "Widgets/Administration/ProvinceDataWidget.h"
#include "Widgets/Economics/StorageGoodsListWidget.h"
#include "Widgets/Events/EventWidget.h"
#include "Widgets/Military/Creation/UnitTypesListWidget.h"
#include "Widgets/Military/Selection/UnitInstancesListDescriptionWidget.h"
#include "Widgets/Military/Supply/UnitsSupplyListWidget.h"
#include "Widgets/Military/Units/UnitInformationListWidget.h"

#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUnitInstancesListDescriptionWidget> UnitInstancesListDescriptionWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUnitsSupplyListWidget> UnitsSupplyListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UStorageGoodsListWidget> StorageGoodsListWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UProvinceDataWidget> ProvinceDataWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUnitTypesListWidget> UnitTypesListWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTimeControllerWidget> TimeControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEventWidget> EventWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUnitInformationListWidget> UnitInformationListWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan MinDeltaBetweenEventChecks = FTimespan(24, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	FDateTime StartTime = FDateTime(1914, 1, 1);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	int MaxTimeSpeed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	float SpeedMultiplier = 0.1;
	
	AMyGameState();

	int GetStability() const;

	void SetStability(int32 Stability);
private:
	int32 Stability = 0;
};
