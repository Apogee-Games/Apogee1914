#include "Division.h"

FDivision::FDivision(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner): FUnit(UnitDescription, Province, CountryOwner)
{
}

FDivision::FDivision(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController): FUnit(UnitDescription, Province, CountryOwner, CountryController)
{
}

EMilitaryBranch FDivision::GetMilitaryBranch() const
{
	return EMilitaryBranch::Army;
}
