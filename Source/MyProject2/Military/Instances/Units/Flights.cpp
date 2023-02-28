#include "Flights.h"

FFlights::FFlights(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner,
	UUnitsRenderer* UnitsRenderer): FUnit(UnitDescription, Province, CountryOwner, UnitsRenderer)
{
}

FFlights::FFlights(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner,
	UCountry* CountryController, UUnitsRenderer* UnitsRenderer): FUnit(UnitDescription, Province, CountryOwner, CountryController, UnitsRenderer)
{
}

EMilitaryBranch FFlights::GetMilitaryBranch() const
{
	return EMilitaryBranch::Navy;
}
