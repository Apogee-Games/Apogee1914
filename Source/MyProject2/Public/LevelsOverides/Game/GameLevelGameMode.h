// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AIPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/AIPlayerPawn.h"
#include "Widgets/Military/Creation/UnitTypesListWidget.h"
#include "GameLevelGameMode.generated.h"

class UProvinceDataWidget;
/**
 * 
 */
UCLASS()
class MYPROJECT2_API AGameLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGameLevelGameMode();

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAIPlayerController> AIPlayerControllerClass; 
	
private:
	/* Creates AIPawns for all non user played countries */
	void CreateAIPawns();

	UPROPERTY()
	TMap<UCountryDescription*, AAIPlayerPawn*> AIPawns;
};