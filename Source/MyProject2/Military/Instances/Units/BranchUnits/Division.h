#pragma once

#include "MyProject2/Military/Instances/Units/Unit.h"

class UDivision: public UUnit
{
public:
	virtual EMilitaryBranch GetMilitaryBranch() const override;

	// TODO: Add CanAccessProvince implementation here :)
};