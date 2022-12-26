// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include <string>
#include <fstream>

#include "FileUtils.h"
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
		LoadProvinces("C:\\Users\\Dklishch\\Documents\\Unreal Projects\\MyProject2\\Content\\provinces_description.csv");
	}
	
	FProvince GetProvince(const FColor& ProvinceColor) const
	{
		return Provinces.Contains(ProvinceColor) ? Provinces[ProvinceColor] : FProvince();
	}

	FColor GetCountryColor(const FColor& ProvinceColor) const
	{
		return Provinces.Contains(ProvinceColor) ? Provinces[ProvinceColor].GetCountryColor() : FColor(20, 20, 20);
	}
private:
	TMap<FColor, FProvince> Provinces;
	
	void LoadProvinces(const FString& ProvinceDescriptionFile)
	{
		std::fstream File(ToCStr(ProvinceDescriptionFile), std::ios_base::in);
		std::string Tmp;

		while (std::getline(File, Tmp))
		{
			FProvince Province = ParseProvince(Tmp);
			Provinces.Add(Province.GetColor(), Province);
		}

		File.close();
	}

	static FProvince ParseProvince(const std::string& Text)
	{
		int Position = 0;
		const FColor Color = ReadColor(Text, Position);
		const std::string Name = FFileUtils::ReadNextValue(Text, Position);
		const int Population = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		const FColor CountryColor = ReadColor(Text, Position);
		return FProvince(Color, FString(Name.c_str()), CountryColor, Population);
	}

	static FColor ReadColor(const std::string& Text, int& Position)
	{
		const int r = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		const int g = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		const int b = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		return FColor(r, g, b);
	}
};
