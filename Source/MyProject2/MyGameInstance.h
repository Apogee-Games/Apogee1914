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

	FString GetRuledCountry(int32 PlayerId) const;

	void SetRuledCountry(int32 PlayerId, const FString& CountryTag);
	
private:
	
	TMap<int32, FString> PlayersRuledCountries;
};
