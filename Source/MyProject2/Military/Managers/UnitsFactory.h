#pragma once
#include "MyProject2/Military/Descriptions/UnitDescription.h"
#include "UnitsRenderer.h"
#include "MyProject2/Military/Instances/Units/Squadron.h"
#include "MyProject2/Military/Interfaces/Observables/UnitCreationObservable.h"
#include "MyProject2/Military/Interfaces/Observables/UnitRemovalObservable.h"
#include "UnitsFactory.generated.h"


UCLASS()
class UUnitsFactory : public UWorldSubsystem, public IUnitCreationObservable, public IUnitRemovalObservable
{
	GENERATED_BODY()
public:
	
	virtual FUnit* Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag);
	
	virtual void Remove(FUnit* Unit);

private:
	FUnit* CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag) const;
};


// TODO: Add remove logic in destructor 
