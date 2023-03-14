#pragma once

#include "Military/Instances/Units/Unit.h"
#include "Division.generated.h"

UCLASS()
class UDivision: public UUnit
{
	GENERATED_BODY()
public:
	virtual EMilitaryBranch GetMilitaryBranch() const override;

	// TODO: Add CanAccessProvince implementation here :)
};