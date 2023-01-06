// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Widgets/TimeController.h"
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
	
	AMyProject2GameModeBase();

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:

	UPROPERTY()
	UTimeController* TimeControllerWidget;
};
