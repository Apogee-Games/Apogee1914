// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::OnStart()
{
	Super::OnStart();
	SetScenario(ActiveScenario);
}

void UMyGameInstance::SetScenario(UScenario* Scenario)
{
	ActiveScenario = Scenario;
	
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
}

const FName& UMyGameInstance::GetRuledCountry(const int32 PlayerId) 
{
	return PlayersRuledCountries[PlayerId];
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
