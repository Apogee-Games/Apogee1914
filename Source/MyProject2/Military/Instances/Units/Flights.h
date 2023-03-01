#pragma once
#include "Unit.h"

class FFlights: FUnit
{
public:
	FFlights(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner);

	FFlights(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController);

	virtual EMilitaryBranch GetMilitaryBranch() const override;
};
