#pragma once

#include "Unit.h"

class FDivision: public FUnit
{
public:
	FDivision(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UUnitsRenderer* UnitsRenderer);

	FDivision(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController, UUnitsRenderer* UnitsRenderer);

	virtual EMilitaryBranch GetMilitaryBranch() const override;

	// TODO: Add CanAccessProvince implementation here :)
};