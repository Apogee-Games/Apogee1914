#pragma once

#include "Military/Instances/Units/Unit.h"
#include "Squadron.generated.h"

UCLASS()
class USquadron: public UUnit
{
	GENERATED_BODY()
public:
	virtual EMilitaryBranch GetMilitaryBranch() const override;
};
