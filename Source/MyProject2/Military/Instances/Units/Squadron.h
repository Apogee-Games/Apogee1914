#pragma once
#include "Unit.h"

class FSquadron: public FUnit
{
public:
	FSquadron(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UUnitsRenderer* UnitsRenderer);

	FSquadron(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController, UUnitsRenderer* UnitsRenderer);

	virtual EMilitaryBranch GetMilitaryBranch() const override;
};
