// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Engine/DataTable.h"
#include "World/Country.h"
#include "World/Province.h"
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
	}

	FProvince GetProvince(const FColor& ProvinceColor) const
	{
		const FProvince* Province = reinterpret_cast<FProvince*>(ProvinceDescriptionDataTable->FindRowUnchecked(FName(ProvinceColor.ToHex())));
		return Province ? *Province : FProvince();
	}

	FColor GetCountryColor(const FColor& ProvinceColor) const
	{		
		const FProvince* Province = reinterpret_cast<FProvince*>(ProvinceDescriptionDataTable->FindRowUnchecked(FName(ProvinceColor.ToHex())));
		if (!Province) return FColor(20, 20, 20);

		const FCountry* Country = reinterpret_cast<FCountry*>(CountryDescriptionDataTable->FindRowUnchecked(FName(Province->CountryTag)));
		return Country ? Country->Color : FColor(20, 20, 20);
	}
	
	UPROPERTY()
	UDataTable* CountryDescriptionDataTable;

	UPROPERTY()
	UDataTable* ProvinceDescriptionDataTable;
};
