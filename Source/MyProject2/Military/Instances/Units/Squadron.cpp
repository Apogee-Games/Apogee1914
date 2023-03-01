#include "Squadron.h"

FSquadron::FSquadron(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner): FUnit(UnitDescription, Province, CountryOwner)
{
}

FSquadron::FSquadron(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController): FUnit(UnitDescription, Province, CountryOwner, CountryController)
{
}

EMilitaryBranch FSquadron::GetMilitaryBranch() const
{
	return EMilitaryBranch::Navy;
}
