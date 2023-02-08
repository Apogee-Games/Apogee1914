#pragma once
#include "MyProject2/Military/Instances/Unit.h"
#include "MyProject2/Military/Descriptions/UnitDescription.h"
#include "UnitsRenderer.h"
#include "UnitsFactory.generated.h"


UCLASS()
class UUnitsFactory : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual UUnit* Create(FUnitDescription* Description, const FColor& Position, const FString& CountryOwnerTag, UUnitsRenderer* Renderer);

	virtual void Remove(UUnit* Unit);
};
