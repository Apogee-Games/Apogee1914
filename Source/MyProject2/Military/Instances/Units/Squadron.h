#pragma once
#include "Unit.h"

class FSquadron: public FUnit
{
public:
	FSquadron(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner);

	FSquadron(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController);

	virtual EMilitaryBranch GetMilitaryBranch() const override;
};