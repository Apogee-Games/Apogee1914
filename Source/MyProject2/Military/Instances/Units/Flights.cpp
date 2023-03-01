#include "Flights.h"

FFlights::FFlights(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner): FUnit(UnitDescription, Province, CountryOwner)
{
}

FFlights::FFlights(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController): FUnit(UnitDescription, Province, CountryOwner, CountryController)
{
}

EMilitaryBranch FFlights::GetMilitaryBranch() const
{
	return EMilitaryBranch::Navy;
}
