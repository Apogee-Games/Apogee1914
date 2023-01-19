// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "Widgets/EventWidget.h"
#include "Widgets/TimeController.h"
#include "Characters/AIPlayerPawn.h"
#include "MyProject2GameModeBase.generated.h"

class UProvinceData;
/**
 * 
 */
UCLASS()
class MYPROJECT2_API AMyProject2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTimeController> TimeControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEventWidget> EventWidgetClass;
	
	AMyProject2GameModeBase();

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan MinDeltaBetweenEventChecks = FTimespan(24, 0, 0);
	
private:

	void InitializeEventModules() const;

	/* Initializes Ruled Country for all human players */
	void InitializeRuledCountry() const;

	/* Initializes Ruled Country for all local human players */
	void InitializeRuledCountryForLocalPlayers() const;

	/* Creates AIPawns for all non user played countries */
	void CreateAIPawns();
	
	UPROPERTY()
	UDataTable* EventsDataTable;

	UPROPERTY()
	UTimeController* TimeControllerWidget;
	
	FEventManager* EventManager;

	bool AreEventConditionCheckersInitialized = false;

	UPROPERTY()
	TMap<FString, AAIPlayerPawn*> AIPawns;
};