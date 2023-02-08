﻿#include "Province.h"

UProvince::UProvince()
{
	Population = NewObject<UProvincePopulation>();
}


void UProvince::Init(FProvinceDescription* ProvinceDescription, const UDataTable* TerrainDT,const UDataTable* FactoryDT)
{
	Id = ProvinceDescription->Color;
	Name = ProvinceDescription->ProvinceName;
	OwnerCountryTag = ProvinceDescription->CountryTag;
	ControllerCountryTag = ProvinceDescription->CountryTag;
	StateId = ProvinceDescription->StateId;
	Resources = ProvinceDescription->Resources;
	Population->Init(ProvinceDescription->Population);
	// Terrain = reinterpret_cast<FTerrainDescription*>(TerrainDT->FindRowUnchecked(FName(ProvinceDescription->TerrainName)));
	
	// for(const auto& FactoryInstanceDescription : ProvinceDescription->Factories)
	// {
	// 	FFactoryDescription* FactoryDescription = reinterpret_cast<FFactoryDescription*>(FactoryDT->FindRowUnchecked(FName(FactoryInstanceDescription.Type)));
	// 	
	// 	UProvinceFactory* ProvinceFactory = NewObject<UProvinceFactory>();
	// 	ProvinceFactory->Init(FactoryInstanceDescription, FactoryDescription);
	// 	Factories.Add(ProvinceFactory);
	// }
}

const FColor& UProvince::GetId() const
{
	return Id;
}

const FString& UProvince::GetOwnerCountryTag() const
{
	return OwnerCountryTag;
}

const FString& UProvince::GetControllerCountryTag() const
{
	return ControllerCountryTag;
}

void UProvince::TakeControl(const FString& CountryTag)
{
	ControllerCountryTag = CountryTag;
}

void UProvince::Conquer(const FString& CountryTag)
{
	OwnerCountryTag = CountryTag;
	ControllerCountryTag = CountryTag;
}

const FString& UProvince::GetStateId() const
{
	return StateId;
}

const FString& UProvince::GetName()
{
	return Name;
}

const UProvincePopulation* UProvince::GetPopulation() const
{
	return Population;
}


const FTerrainDescription* UProvince::GetTerrain() const
{
	return Terrain;
}

const TMap<FString, int> UProvince::GetResources() const
{
	return Resources;
}


