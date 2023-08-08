#include "Military/Instances/Units/Unit.h"

#include "Administration/Managers/CountriesManager.h"
#include "Economics/Description/Goods/MilitaryGoodDescription.h"
#include "Maps/Graph.h"
#include "Military/Managers/UnitsFactory.h"

void UUnit::Init(UUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince)
{
	UnitDescription = ProvidedUnitDescription;
	Province = ProvidedProvince;
	SupplyNeeds = NewObject<UUnitSupplyNeeds>(this);
	SupplyNeeds->Init(ProvidedUnitDescription->EquipmentRequirements);
	Province->AddUnit(this);
	Manpower = UnitDescription->ManpowerRequirements;

	UUnitsFactory* UnitsFactory = Cast<UUnitsFactory>(GetOuter());
	UnitsFactory->OnUnitStatusChanged.Broadcast(this, EUnitStatus::Formed);
}

void UUnit::Dissolve()
{
	UUnitsFactory* UnitsFactory = Cast<UUnitsFactory>(GetOuter());
	UnitsFactory->OnUnitStatusChanged.Broadcast(this, EUnitStatus::Dissolved);
	
	if (UnitsCollection)
	{
		UnitsCollection->Remove(this);
	}

	Province->RemoveUnit(this);
}

bool UUnit::CanTransportUnits() const
{
	return UnitDescription->CanTransport;
}

/*
void UUnit::AddTransportedUnit(UUnit* Unit)
{
	if (!CanTransportUnits()) return;
	TransportedUnits.Add(Unit);
}

void UUnit::RemoveTransportedUnit(UUnit* Unit)
{
	if (!CanTransportUnits()) return;
	TransportedUnits.Remove(Unit);
}*/

void UUnit::Move(UProvince* NewProvince)
{
	if (NewProvince)
	{
		Province->RemoveUnit(this);
		NewProvince->AddUnit(this);

		Province = NewProvince;
	}
}

UProvince* UUnit::GetPosition() const
{
	return Province;
}

int32 UUnit::Estimate(const TArray<FPathElement>& Path)
{
	//TODO: Add additional logic for better estimation
	int32 Result = 0;
	for (const auto& Pair : Path)
	{
		Result += Pair.Cost;
	}
	return Result;
}

int32 UUnit::GetUnitTypeEquipmentRequirement(UGoodDescription* Good) const
{
	return UnitDescription->EquipmentRequirements[Good];
}

UUnitSupplyNeeds* UUnit::GetSupplyNeeds() const
{
	return SupplyNeeds;
}

const FName& UUnit::GetUnitName() const
{
	return UnitDescription->UnitName;
}

UMilitaryBranchDescription* UUnit::GetMilitaryBranch() const
{
	return UnitDescription->MilitaryBranch;
}

void UUnit::SetUnitsCollection(UUnitsCollection* ProvidedUnitsCollection)
{
	 UnitsCollection = ProvidedUnitsCollection;
}

UUnitsCollection* UUnit::GetUnitsCollection() const
{
	return UnitsCollection;
}

float UUnit::GetAttackScore()
{
	float EquipmentSupplyScale = FMath::Max(0.1f, SupplyNeeds->GetSupplyPercentage());
	
	float Score = UnitDescription->Attack * Manpower * (Training + 1) * EquipmentSupplyScale;

	float EquipmentScore = 0;

	for (const auto& [Good, Required]: UnitDescription->EquipmentRequirements)
	{
		UMilitaryGoodDescription* MilitaryGood = Cast<UMilitaryGoodDescription>(Good);
		if (MilitaryGood) {
			EquipmentScore += SupplyNeeds->GetGoodSupply(Good) * MilitaryGood->Attack; // TODO: Think about it again
		}
	}

	return Score + EquipmentScore;
}

float UUnit::GetDefenceScore()
{
	float EquipmentSupplyScale = FMath::Max(0.1f, SupplyNeeds->GetSupplyPercentage());

	float Score = UnitDescription->Defence * Manpower * (Training + 1) * EquipmentSupplyScale;

	float EquipmentScore = 0;

	for (const auto& [Good, Required]: UnitDescription->EquipmentRequirements)
	{
		UMilitaryGoodDescription* MilitaryGood = Cast<UMilitaryGoodDescription>(Good);
		if (MilitaryGood) {
			EquipmentScore += SupplyNeeds->GetGoodSupply(Good) * MilitaryGood->Defence; // TODO: Think about it again
		}
	}

	return Score + EquipmentScore;
}

float UUnit::Damage(float DamageScore)
{
	if (Manpower <= 0 || DamageScore <= 0) return 0;
	float Dead = FMath::Min(Manpower, DamageScore / UnitDescription->PersonDeathScore);
	Manpower -= Dead;
	return Dead * UnitDescription->PersonDeathScore;
}

float UUnit::GetManpower() const
{
	return Manpower;
}

void UUnit::SetIsUnitMoving(bool InbIsUnitMoving)
{
	bIsUnitMoving = InbIsUnitMoving;
}

bool UUnit::IsUnitMoving() const
{
	return bIsUnitMoving;
}

