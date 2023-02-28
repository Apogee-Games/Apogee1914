#include "Squadron.h"

FSquadron::FSquadron(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner,
	UUnitsRenderer* UnitsRenderer): FUnit(UnitDescription, Province, CountryOwner, UnitsRenderer)
{
}

FSquadron::FSquadron(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner,
	UCountry* CountryController, UUnitsRenderer* UnitsRenderer): FUnit(UnitDescription, Province, CountryOwner, CountryController, UnitsRenderer)
{
}

EMilitaryBranch FSquadron::GetMilitaryBranch() const
{
	return EMilitaryBranch::Navy;
}
