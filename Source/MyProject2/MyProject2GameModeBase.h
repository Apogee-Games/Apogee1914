// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Widgets/TimeControllerWidget.h"
#include "Characters/AIPlayerPawn.h"
#include "Widgets/Military/Creation/UnitTypesListWidget.h"
#include "MyProject2GameModeBase.generated.h"

class UProvinceDataWidget;
/**
 * 
 */
UCLASS()
class MYPROJECT2_API AMyProject2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyProject2GameModeBase();

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	/* Initializes Ruled Country for all human players */
	void InitializeRuledCountry() const;

	/* Initializes Ruled Country for all local human players */
	void InitializeRuledCountryForLocalPlayers() const;

	/* Creates AIPawns for all non user played countries */
	void CreateAIPawns();

	UPROPERTY()
	TMap<FName, AAIPlayerPawn*> AIPawns;
};