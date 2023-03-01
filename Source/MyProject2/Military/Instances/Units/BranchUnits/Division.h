#pragma once

#include "MyProject2/Military/Instances/Units/Unit.h"

class FDivision: public FUnit
{
public:
	FDivision(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner);

	FDivision(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController);

	virtual EMilitaryBranch GetMilitaryBranch() const override;

	// TODO: Add CanAccessProvince implementation here :)
};