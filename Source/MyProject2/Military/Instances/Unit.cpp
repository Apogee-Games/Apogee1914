#include "Unit.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Military/Managers/UnitsRenderer.h"

void UUnit::Init(const FUnitDescription* UnitDescription, UProvince* ProvidedProvince, FName ProvidedCountryOwnerTag,
                 UUnitsRenderer* ProvidedUnitsRenderer)
{
	Init(UnitDescription, ProvidedProvince, ProvidedCountryOwnerTag, ProvidedCountryOwnerTag, ProvidedUnitsRenderer);
}

void UUnit::Init(const FUnitDescription* UnitDescription, UProvince* ProvidedProvince, FName ProvidedCountryOwnerTag,
             FName ProvidedCountryControllerTag, UUnitsRenderer* ProvidedUnitsRenderer)
{
	bCanTransportUnits = UnitDescription->CanTransport;
	Province = ProvidedProvince;
	CanAccessProvinceTypes = UnitDescription->CanAccessProvincesTypes;
	UnitsRenderer = ProvidedUnitsRenderer;
	CountryOwner = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(ProvidedCountryOwnerTag);
	CountryController = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(ProvidedCountryControllerTag);
}

bool UUnit::CanTransportUnits() const
{
	return bCanTransportUnits;
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

int UUnit::Estimate(const TArray<TPair<UProvince*, int>>& Path)
{
	//TODO: Add additional logic for better estimation
	int Result = 0;
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

