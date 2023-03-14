#pragma once
#include "Military/Instances/Units/Unit.h"
#include "Flight.generated.h"

UCLASS()
class UFlight: public UUnit
{
	GENERATED_BODY()
public:
	virtual EMilitaryBranch GetMilitaryBranch() const override;
};
