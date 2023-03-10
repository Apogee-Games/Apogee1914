#pragma once

#include "MyProject2/Military/Instances/Units/Unit.h"

class USquadron: public UUnit
{
public:
	virtual EMilitaryBranch GetMilitaryBranch() const override;
};
