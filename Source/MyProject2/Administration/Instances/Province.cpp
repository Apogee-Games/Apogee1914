﻿#include "Province.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"

UProvince::UProvince()
{
	Population = NewObject<UProvincePopulation>();
}

void UProvince::Init(FProvinceDescription* ProvinceDescription, const UDataTable* TerrainDT, const UDataTable* FactoryDT)
{
	Id = ProvinceDescription->Color;
	Name = ProvinceDescription->ProvinceName;
	OwnerCountry = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(ProvinceDescription->CountryTag);
	ControllerCountry = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(ProvinceDescription->CountryTag);
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

UCountry* UProvince::GetOwnerCountry() const
{
	return OwnerCountry;
}

UCountry* UProvince::GetControllerCountry() const
{
	return ControllerCountry;
}

void UProvince::TakeControl(UCountry* Country)
{
	ControllerCountry = Country;
}

void UProvince::Conquer(UCountry* Country)
{
	OwnerCountry = Country;
	ControllerCountry = Country;
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


