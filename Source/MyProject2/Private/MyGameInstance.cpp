// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Actions/ConditionCheckers/ConditionsCheckingSubsystem.h"
#include "Actions/OutcomeAppliers/OutcomesApplierSubsystem.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "GameFramework/PlayerState.h"
#include "Maps/MapController.h"
#include "Maps/MapsDataGatherer.h"
#include "Military/Managers/BattlesManager.h"
#include "Military/Managers/CommandersManager.h"
#include "Military/Managers/UnitsFactory.h"
#include "People/Managers/PeopleManager.h"

void UMyGameInstance::OnStart()
{
	Super::OnStart();
	
	Managers = {
		GetSubsystem<UInGameTime>(),
		
		GetSubsystem<ULawsManager>(),
		GetSubsystem<UPeopleManager>(),
		GetSubsystem<UCountriesManager>(),
		GetSubsystem<UProvinceManager>(),
		GetSubsystem<UStateManager>(),

		GetSubsystem<UMapsDataGatherer>(),
		GetSubsystem<UMapController>(),

		GetSubsystem<URelationshipsManager>(),

		GetSubsystem<UGoodsManager>(),
		GetSubsystem<UStrataManager>(),
		GetSubsystem<UBuildingManager>(),
		
		GetSubsystem<UUnitsFactory>(),
		GetSubsystem<UUnitsMover>(),
		GetSubsystem<UCommandersManager>(),
		GetSubsystem<UUnitsSupplyController>(),
		GetSubsystem<UBattlesManager>(),

		GetSubsystem<UConditionsCheckingSubsystem>(),
		GetSubsystem<UEventInstancesController>(),
		GetSubsystem<UOutcomesApplierSubsystem>()
	};
}

void UMyGameInstance::SetScenario(UScenario* Scenario)
{
	if (ActiveScenario == Scenario) return;
	ActiveScenario = Scenario;
	InitializeActiveScenario();
}

UCountry* UMyGameInstance::GetRuledCountry(APlayerController* PlayerController)
{
	int32 PlayerId = GetTypeHash(PlayerController->GetPlayerState<APlayerState>()->GetUniqueId());
	return GetRuledCountry(PlayerId);
}

UCountry* UMyGameInstance::GetRuledCountry(const int32 PlayerId) 
{
	return PlayersRuledCountries[PlayerId];
}

void UMyGameInstance::SetRuledCountry(APlayerController* PlayerController, UCountry* Country)
{
	int32 PlayerId = GetTypeHash(PlayerController->GetPlayerState<APlayerState>()->GetUniqueId());
	SetRuledCountry(PlayerId, Country);
}

void UMyGameInstance::SetRuledCountry(const int32 PlayerId, UCountry* Country)
{
	if (PlayersRuledCountries.Contains(PlayerId)) CountriesRuledByPlayers[PlayersRuledCountries[PlayerId]->GetId()]--;
	PlayersRuledCountries.Add(PlayerId, Country);
	CountriesRuledByPlayers.Add(Country->GetId(), CountriesRuledByPlayers.Contains(Country->GetId()) ? CountriesRuledByPlayers[Country->GetId()] + 1 : 1);
	OnRuledCountrySelected.Broadcast(PlayerId, Country);
}

bool UMyGameInstance::IsCountryRuledByPlayer(UCountryDescription* CountryDescription)
{
	return CountriesRuledByPlayers.Contains(CountryDescription) && CountriesRuledByPlayers[CountryDescription];
}

void UMyGameInstance::ClearSelectedCountries()
{
	CountriesRuledByPlayers.Empty();
	PlayersRuledCountries.Empty();
}

void UMyGameInstance::NotifyStageIsLoaded(ELoadStage Stage)
{
	AsyncTask(ENamedThreads::GameThread, [this, Stage]()
	{
		OnStageLoadFinished.Broadcast(Stage);
	});
}

void UMyGameInstance::InitializeActiveScenario()
{
	AsyncTask(ENamedThreads::AnyThread, [this]()
	{
		NotifyStageIsLoaded(ELoadStage::Initial);
		
		for (const auto& Manager: Managers)
		{
			Manager->SetScenario(ActiveScenario);
			NotifyStageIsLoaded(Manager->GetLoadStage());
		}

		NotifyStageIsLoaded(ELoadStage::Finished);
	});
}
