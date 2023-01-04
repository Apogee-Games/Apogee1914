// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Engine/DataTable.h"
#include "World/Country.h"
#include "World/Province.h"
#include "World/State.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMyGameState()
	{
		const ConstructorHelpers::FObjectFinder<UDataTable> ProvincesDescriptionFinder(TEXT("/Game/Sources/provinces_description"));
		if (ProvincesDescriptionFinder.Succeeded())
		{
			ProvinceDescriptionDataTable = ProvincesDescriptionFinder.Object;
		}

		const ConstructorHelpers::FObjectFinder<UDataTable> CountriesDescriptionFinder(TEXT("/Game/Sources/countries_description"));
		if (CountriesDescriptionFinder.Succeeded())
		{
			CountryDescriptionDataTable = CountriesDescriptionFinder.Object;
		}
		
		const ConstructorHelpers::FObjectFinder<UDataTable> StateDescriptionFinder(TEXT("/Game/Sources/states_description"));
		if (StateDescriptionFinder.Succeeded())
		{
			StateDescriptionDataTable = StateDescriptionFinder.Object;
		}
	}

	FProvince GetProvince(const FColor& ProvinceColor) const
	{
		if (ProvinceColor == FColor(0, 0, 0) || ProvinceColor == FColor(255, 255, 255)) return FProvince();
		const FProvince* Province = reinterpret_cast<FProvince*>(ProvinceDescriptionDataTable->FindRowUnchecked(FName(ProvinceColor.ToHex())));
		return Province ? *Province : FProvince();
	}
	
	FColor GetCountryColor(const FColor& ProvinceColor) const
	{
		if (ProvinceColor == FColor(0, 0, 0) || ProvinceColor == FColor(255, 255, 255)) return FColor(20, 20, 20);
		const FProvince* Province = reinterpret_cast<FProvince*>(ProvinceDescriptionDataTable->FindRowUnchecked(FName(ProvinceColor.ToHex())));
		if (!Province) return FColor(20, 20, 20);

		const FCountry* Country = reinterpret_cast<FCountry*>(CountryDescriptionDataTable->FindRowUnchecked(FName(Province->CountryTag)));
		return Country ? Country->Color : FColor(20, 20, 20);
	}

	FState GetState(const FString& StateId) const 
	{
		const FState* State = reinterpret_cast<FState*>(StateDescriptionDataTable->FindRowUnchecked(FName(StateId)));
		return State ? *State : FState();
	}
	
	UPROPERTY()
	UDataTable* CountryDescriptionDataTable;

	UPROPERTY()
	UDataTable* ProvinceDescriptionDataTable;

	UPROPERTY()
	UDataTable* StateDescriptionDataTable;
};
