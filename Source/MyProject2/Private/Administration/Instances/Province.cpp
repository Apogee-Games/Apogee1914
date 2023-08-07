
#include "Administration/Instances/Province.h"

#include "MyGameInstance.h"
#include "Administration/Managers/CountriesManager.h"
#include "Administration/Managers/ProvinceManager.h"
#include "LevelsOverides/Game/GameLevelGameMode.h"
#include "Military/Instances/Units/Unit.h"
#include "Military/Managers/BattlesManager.h"

UProvince::UProvince()
{
	Population = CreateDefaultSubobject<UProvincePopulation>(TEXT("Population"));
}

void UProvince::Init(UProvinceDescription* ProvinceDescription)
{
	Id = ProvinceDescription->Color;
	Name = ProvinceDescription->Name;

	UMyGameInstance* GameInstance = GetWorld()->GetGameInstance<UMyGameInstance>();
	
	UCountriesManager* CountriesManager = GameInstance->GetSubsystem<UCountriesManager>();
	
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

void UProvince::InitProvinceActor(FVector Location, FVector2d TopLeft, FVector2d BottomRight)
{
	FActorSpawnParameters Parameters;
	Parameters.Name = FName(Name.ToString() + ControllerCountry->GetId()->Tag.ToString());
	ProvinceActor = GetWorld()->SpawnActor<AProvinceActor>(GetWorld()->GetGameInstance<UMyGameInstance>()->ProvinceActorClass, Parameters);
	ProvinceActor->Init(Name, TopLeft, BottomRight);
#if WITH_EDITOR
	ProvinceActor->SetActorLabel(Name.ToString() + ControllerCountry->GetId()->Tag.ToString());
#endif
	ProvinceActor->SetActorLocation(Location);
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

void UProvince::UpdateControllerCountry()
{
	if (Units.IsEmpty() && !Attackers.IsEmpty())
	{
		TakeControl(Attackers[0]->GetCountryController());
		for (const auto& Attacker : Attackers)
		{
			Units.Add(Attacker);
		}
		Attackers.Empty();
	}
}

void UProvince::TakeControl(UCountry* Country)
{
	UCountry* PreviousController = ControllerCountry;
	
	ControllerCountry->RemoveProvince(this);
	Country->AddProvince(this);
	ControllerCountry = Country;

	FOnProvinceHasNewController& OnProvinceHasNewController = Cast<UProvinceManager>(GetOuter())->OnProvinceHasNewController;
	if (OnProvinceHasNewController.IsBound())
	{
		OnProvinceHasNewController.Broadcast(this, PreviousController, Country);
	}
}

void UProvince::Conquer(UCountry* Country)
{
	UCountry* PreviousOwner = OwnerCountry;
	
	OwnerCountry = Country;
	ControllerCountry = Country;

	FOnProvinceHasNewOwner& OnProvinceHasNewOwner = Cast<UProvinceManager>(GetOuter())->OnProvinceHasNewOwner;
	if (OnProvinceHasNewOwner.IsBound())
	{
		OnProvinceHasNewOwner.Broadcast(this, PreviousOwner, Country);
	}
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
	if (ControllerCountry->IsInWarWith(Unit->GetCountryController()))
	{
		Attackers.Add(Unit);
		ProvinceActor->AddAttacker(Unit);
		if (Attackers.Num() == 1)
		{
			GetWorld()->GetGameInstance()->GetSubsystem<UBattlesManager>()->AddBattle(this);
		}
	} else
	{
		Units.Add(Unit);
		ProvinceActor->AddDefender(Unit);
	}
}

void UProvince::RemoveUnit(UUnit* Unit)
{
	if (Units.Contains(Unit))
	{
		ProvinceActor->RemoveDefender(Unit);
		Units.Remove(Unit);
	} else {
		ProvinceActor->RemoveAttacker(Unit);
		Attackers.Remove(Unit);
	}
}

const TArray<UUnit*>& UProvince::GetUnits() const
{
	return Units;
}

const TArray<UBuilding*>& UProvince::GetBuildings() const
{
	return Buildings;
}

const TArray<UUnit*>& UProvince::GetAttackers() const
{
	return Attackers;
}

const TArray<UUnit*>& UProvince::GetDefenders() const
{
	return Units;
}


