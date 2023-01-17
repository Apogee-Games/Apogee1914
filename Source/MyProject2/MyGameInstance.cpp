// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

FString UMyGameInstance::GetRuledCountry(const int32 PlayerId) const
{
	return PlayersRuledCountries[PlayerId];
}

void UMyGameInstance::SetRuledCountry(const int32 PlayerId, const FString& CountryTag)
{
	PlayersRuledCountries.Add(PlayerId, CountryTag);
}
