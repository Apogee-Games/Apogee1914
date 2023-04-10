
#include "Administration/Instances/Province.h"

#include "Administration/Managers/CountriesManager.h"
#include "Administration/Managers/ProvinceManager.h"

UProvince::UProvince()
{
	Population = CreateDefaultSubobject<UProvincePopulation>(TEXT("Population"));
}

void UProvince::Init(UProvinceDescription* ProvinceDescription)
{
	Id = ProvinceDescription->Color;
	Name = ProvinceDescription->Name;

	UCountriesManager* CountriesManager = GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>();
	
	OwnerCountry = CountriesManager->GetCountry(ProvinceDescription->Country);
	ControllerCountry = CountriesManager->GetCountry(ProvinceDescription->Country);
	
	State = ProvinceDescription->State;
	
	Resources = NewObject<UProvinceResources>(this);
	Resources->Init(ProvinceDescription->Resources);

	Population->Init(ProvinceDescription->Population);

	if (ControllerCountry)
	{
		ControllerCountry->AddProvince(this);
	} else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("No Country %s"), *ProvinceDescription->Country->Tag.ToString()));
		}
	}
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
	ControllerCountry->RemoveProvince(this);
	Country->AddProvince(this);
	ControllerCountry = Country;
	Cast<UProvinceManager>(GetOuter())->NotifyProvinceNewControllingCountry(this);
}

void UProvince::Conquer(UCountry* Country)
{
	OwnerCountry = Country;
	ControllerCountry = Country;
	//Cast<UProvinceManager>(GetOuter())->NotifyProvinceNewOwningCountry(this);
}

UStateDescription* UProvince::GetState() const
{
	return State;
}

const FText& UProvince::GetName()
{
	return Name;
}

const UProvincePopulation* UProvince::GetPopulation() const
{
	return Population;
}


UTerrainDescription* UProvince::GetTerrain() const
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

void UProvince::AddUnit(UUnit* Unit)
{
	Units.Add(Unit);
}

void UProvince::RemoveUnit(UUnit* Unit)
{
	Units.Remove(Unit);
}

const TArray<UUnit*>& UProvince::GetUnits() const
{
	return Units;
}

const TArray<UBuilding*>& UProvince::GetBuildings() const
{
	return Buildings;
}


