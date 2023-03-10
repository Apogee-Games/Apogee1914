#pragma once
#include "Military/Instances/Units/Unit.h"

class UFlight: public UUnit
{
public:
	virtual EMilitaryBranch GetMilitaryBranch() const override;
};
