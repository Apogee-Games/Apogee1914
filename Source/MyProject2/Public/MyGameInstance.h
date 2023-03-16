// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGameTime.h"
#include "Scenario.h"
#include "Engine/GameInstance.h"
#include "Events/EventInstancesController.h"
#include "Military/Managers/UnitsRenderer.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	const FName& GetRuledCountry(int32 PlayerId);

	void SetRuledCountry(int32 PlayerId, const FName& CountryTag);

	bool IsCountryRuledByPlayer(const FName& CountryTag);

	UPROPERTY(EditDefaultsOnly)
	TArray<UScenario*> Scenarios;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) 
	TSubclassOf<UInGameTime> InGameTimeClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) 
	TSubclassOf<UUnitsRenderer> UnitsRendererClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	TSubclassOf<UEventInstancesController> EventInstancesControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UScenario* ActiveScenario;
private:
	TMap<int32, FName> PlayersRuledCountries;

	TMap<FName, int32> CountriesRuledByPlayers;
};
