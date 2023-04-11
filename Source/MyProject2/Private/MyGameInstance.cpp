// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Actions/ConditionCheckers/ConditionsCheckingSubsystem.h"
#include "Actions/OutcomeAppliers/OutcomesApplierSubsystem.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "GameFramework/PlayerState.h"
#include "Maps/Diplomacy/CountryRelationMap.h"
#include "Military/Managers/BattlesManager.h"
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
}

bool UMyGameInstance::IsCountryRuledByPlayer(UCountryDescription* CountryDescription)
{
	return CountriesRuledByPlayers.Contains(CountryDescription) && CountriesRuledByPlayers[CountryDescription];

}

void UMyGameInstance::InitializeActiveScenario()
{
	GetSubsystem<UInGameTime>()->SetScenario(ActiveScenario);

	GetSubsystem<ULawsManager>()->SetScenario(ActiveScenario);
	
	GetSubsystem<UPeopleManager>()->SetScenario(ActiveScenario);

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
	GetSubsystem<UBattlesManager>()->SetScenario(ActiveScenario);
	
	GetSubsystem<UConditionsCheckingSubsystem>()->SetScenario(ActiveScenario);
	GetSubsystem<UEventInstancesController>()->SetScenario(ActiveScenario);
	GetSubsystem<UOutcomesApplierSubsystem>()->SetScenario(ActiveScenario);
}
