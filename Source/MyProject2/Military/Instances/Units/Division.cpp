#include "Division.h"

FDivision::FDivision(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner,
	UUnitsRenderer* UnitsRenderer): FUnit(UnitDescription, Province, CountryOwner, UnitsRenderer)
{
}

FDivision::FDivision(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner,
	UCountry* CountryController, UUnitsRenderer* UnitsRenderer): FUnit(UnitDescription, Province, CountryOwner, CountryController, UnitsRenderer)
{
}

EMilitaryBranch FDivision::GetMilitaryBranch() const
{
	return EMilitaryBranch::Army;
}
