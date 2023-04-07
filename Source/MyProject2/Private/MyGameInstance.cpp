// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Actions/ConditionCheckers/ConditionsCheckingSubsystem.h"
#include "Actions/OutcomeAppliers/OutcomesApplierSubsystem.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "GameFramework/PlayerState.h"
#include "Maps/Diplomacy/CountryRelationMap.h"
#include "Military/Managers/CommandersManager.h"
#include "Military/Managers/UnitsFactory.h"
#include "People/Managers/PeopleManager.h"

void UMyGameInstance::OnStart()
{
	Super::OnStart();
}

void UMyGameInstance::SetScenario(UScenario* Scenario)
{
	if (ActiveScenario == Scenario) return;
	ActiveScenario = Scenario;
	InitializeActiveScenario();
}

const FName& UMyGameInstance::GetRuledCountry(APlayerController* PlayerController)
{
	int32 PlayerId = GetTypeHash(PlayerController->GetPlayerState<APlayerState>()->GetUniqueId());
	return GetRuledCountry(PlayerId);
}

const FName& UMyGameInstance::GetRuledCountry(const int32 PlayerId) 
{
	return PlayersRuledCountries[PlayerId];
}

void UMyGameInstance::SetRuledCountry(APlayerController* PlayerController, UCountry* Country)
{
	int32 PlayerId = GetTypeHash(PlayerController->GetPlayerState<APlayerState>()->GetUniqueId());
	SetRuledCountry(PlayerId, Country->GetTag());
}

void UMyGameInstance::SetRuledCountry(const int32 PlayerId, const FName& CountryTag)
{
	if (PlayersRuledCountries.Contains(PlayerId)) CountriesRuledByPlayers[PlayersRuledCountries[PlayerId]]--;
	PlayersRuledCountries.Add(PlayerId, CountryTag);
	CountriesRuledByPlayers.Add(CountryTag,
	                            CountriesRuledByPlayers.Contains(CountryTag)
		                            ? CountriesRuledByPlayers[CountryTag] + 1
		                            : 1);
}

bool UMyGameInstance::IsCountryRuledByPlayer(const FName& CountryTag)
{
	return CountriesRuledByPlayers.Contains(CountryTag) && CountriesRuledByPlayers[CountryTag];
}

void UMyGameInstance::InitializeActiveScenario()
{
	GetSubsystem<UInGameTime>()->SetScenario(ActiveScenario);

	GetSubsystem<ULawsManager>()->SetScenario(ActiveScenario);
	
	GetSubsystem<UPeopleManager>()->SetScenario(ActiveScenario);

	GetSubsystem<UIdeologyManager>()->SetScenario(ActiveScenario);
	
	GetSubsystem<UCountriesManager>()->SetScenario(ActiveScenario);
	GetSubsystem<UProvinceManager>()->SetScenario(ActiveScenario);
	GetSubsystem<UStateManager>()->SetScenario(ActiveScenario);

	GetSubsystem<UProvincesMap>()->SetScenario(ActiveScenario);
	GetSubsystem<UDistancesMap>()->SetScenario(ActiveScenario);
	GetSubsystem<UBoxesMap>()->SetScenario(ActiveScenario);
	GetSubsystem<UOutlineMap>()->SetScenario(ActiveScenario);
	GetSubsystem<UObjectMap>()->SetScenario(ActiveScenario);
	GetSubsystem<UFlagsMap>()->SetScenario(ActiveScenario);
	GetSubsystem<UCountriesMap>()->SetScenario(ActiveScenario);
	GetSubsystem<USelectionMap>()->SetScenario(ActiveScenario);

	GetSubsystem<UCountryRelationMap>()->SetScenario(ActiveScenario);
	GetSubsystem<UAlliancesMap>()->SetScenario(ActiveScenario);

	GetSubsystem<URelationshipsManager>()->SetScenario(ActiveScenario);
	GetSubsystem<UIdeologiesMap>()->SetScenario(ActiveScenario);

	GetSubsystem<UMapsSwitcher>()->SetScenario(ActiveScenario);

	GetSubsystem<UGoodsManager>()->SetScenario(ActiveScenario);
	GetSubsystem<UStrataManager>()->SetScenario(ActiveScenario);
	GetSubsystem<UBuildingManager>()->SetScenario(ActiveScenario);
	
	GetSubsystem<UUnitsFactory>()->SetScenario(ActiveScenario);
	GetSubsystem<UUnitsRenderer>()->SetScenario(ActiveScenario);
	GetSubsystem<UUnitsMover>()->SetScenario(ActiveScenario);
	GetSubsystem<UCommandersManager>()->SetScenario(ActiveScenario);
	GetSubsystem<UUnitsSupplyController>()->SetScenario(ActiveScenario);
	
	GetSubsystem<UConditionsCheckingSubsystem>()->SetScenario(ActiveScenario);
	GetSubsystem<UEventInstancesController>()->SetScenario(ActiveScenario);
	GetSubsystem<UOutcomesApplierSubsystem>()->SetScenario(ActiveScenario);
}
