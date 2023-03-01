#pragma once
#include "MyProject2/Military/Instances/Units/Unit.h"

class FFlight: public FUnit
{
public:
	FFlight(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner);

	FFlight(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController);

	virtual EMilitaryBranch GetMilitaryBranch() const override;
};
