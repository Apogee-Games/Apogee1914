// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

FString UMyGameInstance::GetRuledCountry(const int32 PlayerId) const
{
	return PlayersRuledCountries[PlayerId];
}

void UMyGameInstance::SetRuledCountry(const int32 PlayerId, const FString& CountryTag)
{
	if (PlayersRuledCountries.Contains(PlayerId)) CountriesRuledByPlayers[PlayersRuledCountries[PlayerId]]--;
	PlayersRuledCountries.Add(PlayerId, CountryTag);
	CountriesRuledByPlayers.Add(CountryTag,
	                            CountriesRuledByPlayers.Contains(CountryTag)
		                            ? CountriesRuledByPlayers[CountryTag] + 1
		                            : 1);
}

bool UMyGameInstance::IsCountryRuledByPlayer(const FString& CountryTag)
{
	return CountriesRuledByPlayers.Contains(CountryTag) && CountriesRuledByPlayers[CountryTag];
}
