#pragma once

#include "Military/Instances/Units/Unit.h"

class USquadron: public UUnit
{
public:
	virtual EMilitaryBranch GetMilitaryBranch() const override;
};
