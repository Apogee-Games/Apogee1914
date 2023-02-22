// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	const FName& GetRuledCountry(int32 PlayerId) const;

	void SetRuledCountry(int32 PlayerId, const FName& CountryTag);

	bool IsCountryRuledByPlayer(const FName& CountryTag);

private:
	TMap<int32, FName> PlayersRuledCountries;

	TMap<FName, int32> CountriesRuledByPlayers;
};
