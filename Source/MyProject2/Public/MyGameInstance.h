// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGameTime.h"
#include "Scenario.h"
#include "Administration/Managers/LawsManager.h"
#include "Administration/Managers/StateManager.h"
#include "Administration/Managers/CountriesManager.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "Economics/Managers/BuildingManager.h"
#include "Economics/Managers/GoodsManager.h"
#include "Economics/Managers/StrataManager.h"
#include "Engine/GameInstance.h"
#include "Events/EventInstancesController.h"
#include "Military/Managers/BattlesManager.h"
#include "Military/Managers/UnitsMover.h"
#include "Military/Managers/UnitsSupplyController.h"
#include "MyGameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageLoadFinished, ELoadStage)

UCLASS()
class MYPROJECT2_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void OnStart() override;

	void SetScenario(UScenario* Scenario);

	void InitializeActiveScenario();

	UCountry* GetRuledCountry(APlayerController* PlayerController);
	
	UCountry* GetRuledCountry(int32 PlayerId);

	void SetRuledCountry(APlayerController* PlayerController, UCountry* Country);
	
	void SetRuledCountry(int32 PlayerId, UCountry* Country);

	bool IsCountryRuledByPlayer(UCountryDescription* CountryDescription);

	UPROPERTY(EditDefaultsOnly)
	TArray<UScenario*> Scenarios;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UScenario* ActiveScenario;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProvinceActor> ProvinceActorClass;

	FOnStageLoadFinished OnStageLoadFinished;
private:
	UPROPERTY()
	TArray<UBaseManager*> Managers;
	
	UPROPERTY()
	TMap<int32, UCountry*> PlayersRuledCountries;

	UPROPERTY()
	TMap<UCountryDescription*, int32> CountriesRuledByPlayers;

	void NotifyStageIsLoaded(ELoadStage Stage);
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) 
	TSubclassOf<UInGameTime> InGameTimeClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	TSubclassOf<UEventInstancesController> EventInstancesControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCountriesManager> CountriesManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<URelationshipsManager> RelationshipsManagerClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UProvinceManager> ProvinceManagerClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UStateManager> StateManagerClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBuildingManager> BuildingManagerClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGoodsManager> GoodManagerClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UStrataManager> StrataManagerClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUnitsMover> UnitsMoverClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUnitsSupplyController> UnitsSupplyControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ULawsManager> LawManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBattlesManager> BattlesManagerClass;
};
