#include "Unit.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"

void UUnit::Init(const FUnitDescription* UnitDescription, const FColor& ProvidedProvinceColor, FString ProvidedCountryOwnerTag,
                 UUnitsRenderer* ProvidedUnitsRenderer)
{
	Init(UnitDescription, ProvidedProvinceColor, ProvidedCountryOwnerTag, ProvidedCountryOwnerTag, ProvidedUnitsRenderer);
}

void UUnit::Init(const FUnitDescription* UnitDescription, const FColor& ProvidedProvinceColor, FString ProvidedCountryOwnerTag,
             FString ProvidedCountryControllerTag, UUnitsRenderer* ProvidedUnitsRenderer)
{
	bCanTransportUnits = UnitDescription->CanTransport;
	ProvinceColor = ProvidedProvinceColor;
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

void UUnit::Move(FColor NewProvinceColor)
{
	UnitsRenderer->UnitIsMoved(this, ProvinceColor, NewProvinceColor);
	ProvinceColor = NewProvinceColor;
}

FColor UUnit::GetPosition() const
{
	return ProvinceColor;
}

int UUnit::Estimate(const TArray<TPair<FColor, int>>& Path)
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

