#pragma once
#include <string>
#include <fstream>
#include "Province.h"
#include "MyProject2/FileUtils.h"

class FWorld
{
public:
	FWorld(const FString& ProvinceDescriptionFile)
	{
		LoadProvinces(ToCStr(ProvinceDescriptionFile));
	}

	FProvince GetProvince(const FColor& Color) const
	{
		return Provinces.Contains(Color) ? Provinces[Color] : FProvince();
	}

private:
	TMap<FColor, FProvince> Provinces;

	void LoadProvinces(const TCHAR* ProvinceDescriptionFile)
	{
		std::fstream File(ProvinceDescriptionFile, std::ios_base::in);
		std::string Tmp;

		while (std::getline(File, Tmp))
		{
			FProvince Province = ParseProvince(Tmp);
			Provinces.Add(Province.GetColor(), Province);
			//Provinces[] = Province;
		}

		File.close();
	}

	static FProvince ParseProvince(const std::string& Text)
	{
		int Position = 0;
		const FColor Color = ReadColor(Text, Position);
		const std::string Name = FFileUtils::ReadNextValue(Text, Position);
		const FColor CountryColor = ReadColor(Text, Position);
		return FProvince(Color, FString(Name.c_str()), CountryColor);
	}

	static FColor ReadColor(const std::string& Text, int& Position)
	{
		const int r = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		const int g = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		const int b = std::stoi(FFileUtils::ReadNextValue(Text, Position));
		return FColor(r, g, b);
	}

	
};
