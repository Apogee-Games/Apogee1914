// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include <string>
#include <fstream>

#include "FileUtils.h"
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
		LoadProvinces(
			"C:\\Users\\Dklishch\\Documents\\Unreal Projects\\MyProject2\\Content\\provinces_description.csv");
		LoadCountries(
			"C:\\Users\\Dklishch\\Documents\\Unreal Projects\\MyProject2\\Content\\countries_description.csv");
	}

	FProvince GetProvince(const FColor& ProvinceColor) const
	{
		return Provinces.Contains(ProvinceColor) ? Provinces[ProvinceColor] : FProvince();
	}

	FColor GetCountryColor(const FColor& ProvinceColor) const
	{
		return !Provinces.Contains(ProvinceColor)
			       ? FColor(20, 20, 20)
			       : Countries[Provinces[ProvinceColor].GetCountryTag()].GetColor();
	}

	TSet<FColor> GetProvincesColors() const
	{
		return ProvincesColors;
	}

private:
	TMap<FColor, FProvince> Provinces;
	TMap<FString, FCountry> Countries;

	TSet<FColor> ProvincesColors;

	void LoadCountries(const FString& CountriesDescriptionFile)
	{
		std::fstream File(ToCStr(CountriesDescriptionFile), std::ios_base::in);
		std::string Tmp;

		while (std::getline(File, Tmp))
		{
			FCountry Country = ParseCountry(Tmp);
			Countries.Add(Country.GetTag(), Country);
		}

		File.close();
	}

	void LoadProvinces(const FString& ProvinceDescriptionFile)
	{
		std::fstream File(ToCStr(ProvinceDescriptionFile), std::ios_base::in);
		std::string Tmp;

		while (std::getline(File, Tmp))
		{
			FProvince Province = ParseProvince(Tmp);
			Provinces.Add(Province.GetColor(), Province);
			ProvincesColors.Add(Province.GetColor());
		}

		File.close();
	}

	static FCountry ParseCountry(const std::string& Text)
	{
		int Position = 0;
		const std::string Tag = FFileUtils::ReadNextValue(Text, Position);
		const FColor Color = ReadColor(Text, Position);
		return FCountry(FString(Tag.c_str()), Color);
	}

	static FProvince ParseProvince(const std::string& Text)
	{
		int Position = 0;
		const FColor Color = ReadColor(Text, Position);
		const std::string Name = FFileUtils::ReadNextValue(Text, Position);
		const int Population = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		const std::string Tag = FFileUtils::ReadNextValue(Text, Position);
		return FProvince(Color, FString(Name.c_str()), FString(Tag.c_str()), Population);
	}

	static FColor ReadColor(const std::string& Text, int& Position)
	{
		const int r = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		const int g = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		const int b = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		return FColor(r, g, b);
	}
};
