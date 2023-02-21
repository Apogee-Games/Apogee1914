// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

FName UMyGameInstance::GetRuledCountry(const int32 PlayerId) const
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
