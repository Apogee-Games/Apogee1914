#pragma once
#include "PlayablePawn.h"

#include "CountrySelectionPawn.generated.h"

UCLASS()
class ACountrySelectionPawn: public APlayablePawn
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};
