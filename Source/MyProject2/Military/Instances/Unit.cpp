#include "Unit.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Military/Managers/UnitsRenderer.h"

void UUnit::Init(const FUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince, const FName& ProvidedCountryOwnerTag,
                 UUnitsRenderer* ProvidedUnitsRenderer)
{
	Init(ProvidedUnitDescription, ProvidedProvince, ProvidedCountryOwnerTag, ProvidedCountryOwnerTag, ProvidedUnitsRenderer);
}

void UUnit::Init(const FUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince, const FName& ProvidedCountryOwnerTag,
             const FName& ProvidedCountryControllerTag, UUnitsRenderer* ProvidedUnitsRenderer)
{
	UnitDescription = ProvidedUnitDescription;

	Province = ProvidedProvince;

	UnitsRenderer = ProvidedUnitsRenderer;

	CountryOwner = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(ProvidedCountryOwnerTag);
	CountryController = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(ProvidedCountryControllerTag);

	for (auto& [GoodName, GoodCount]: UnitDescription->EquipmentRequirements)
	{
		EquipmentNeeds.Add(GoodName, GoodCount);
	}
}

bool UUnit::CanTransportUnits() const
{
	return UnitDescription->CanTransport;
}

void UUnit::AddTransportedUnit(UUnit* Unit)
{
	if (!CanTransportUnits()) return;
	TransportedUnits.Add(Unit);
}

void UUnit::RemoveTransportedUnit(UUnit* Unit)
{
	if (!CanTransportUnits()) return;
	TransportedUnits.Remove(Unit);
}

void UUnit::Move(UProvince* NewProvince)
{
	Province = NewProvince;
}

UProvince* UUnit::GetPosition() const
{
	return Province;
}

int32 UUnit::Estimate(const TArray<TPair<UProvince*, int>>& Path)
{
	//TODO: Add additional logic for better estimation
	int32 Result = 0;
	for (const auto& Pair : Path)
	{
		Result += Pair.Value;
	}
	return Result;
}

UCountry* UUnit::GetCountryOwner() const
{
	return CountryOwner;
}

UCountry* UUnit::GetCountryController() const
{
	return CountryController;
}

const TMap<FName, int32>& UUnit::GetEquipmentNeeds() const
{
	return EquipmentNeeds;
}

void UUnit::SupplyEquipment(const FName& GoodName, int32 Amount)
{
	EquipmentNeeds[GoodName] -= Amount;
}

