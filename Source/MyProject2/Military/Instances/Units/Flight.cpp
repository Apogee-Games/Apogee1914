#include "Flight.h"

FFlight::FFlight(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner): FUnit(UnitDescription, Province, CountryOwner)
{
}

FFlight::FFlight(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController): FUnit(UnitDescription, Province, CountryOwner, CountryController)
{
}

EMilitaryBranch FFlight::GetMilitaryBranch() const
{
	return EMilitaryBranch::Navy;
}
