#pragma once
#include "Unit.h"

class FFlights: FUnit
{
public:
	FFlights(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UUnitsRenderer* UnitsRenderer);

	FFlights(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController, UUnitsRenderer* UnitsRenderer);

	virtual EMilitaryBranch GetMilitaryBranch() const override;
};
