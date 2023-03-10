
#include "Administration/Instances/Province.h"

#include "Administration/Managers/CountriesManager.h"

UProvince::UProvince()
{
	Population = NewObject<UProvincePopulation>();
}

void UProvince::Init(FProvinceDescription* ProvinceDescription, const UDataTable* TerrainDT, const UDataTable* FactoryDT, const UDataTable* ResourcesDescriptions)
{
	Id = ProvinceDescription->Color;
	Name = ProvinceDescription->ProvinceName;
	OwnerCountry = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(ProvinceDescription->CountryTag);
	ControllerCountry = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(ProvinceDescription->CountryTag);
	StateId = ProvinceDescription->StateId;
	
	Resources = NewObject<UProvinceResources>();
	for (const auto& [ResourceName, ResourceAmount]: ProvinceDescription->Resources)
	{
		Resources->AddResource(ResourcesDescriptions->FindRowUnchecked(ResourceName), ResourceAmount);
	}

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

UCountry* UProvince::GetCountryController() const
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

const FName& UProvince::GetStateId() const
{
	return StateId;
}

const FName& UProvince::GetName()
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

UProvinceResources* UProvince::GetResources() const
{
	return Resources;
}

void UProvince::AddBuilding(UBuilding* Building)
{
	Buildings.Add(Building);
}

void UProvince::RemoveBuilding(UBuilding* Building)
{
	Buildings.Remove(Building);
}

const TArray<UBuilding*>& UProvince::GetBuildings() const
{
	return Buildings;
}


