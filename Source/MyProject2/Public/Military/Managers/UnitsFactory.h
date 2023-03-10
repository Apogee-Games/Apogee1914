#pragma once

class UUnit;

#include "Military/Descriptions/UnitDescription.h"
#include "Military/Interfaces/Observables/UnitCreationObservable.h"
#include "Military/Interfaces/Observables/UnitRemovalObservable.h"
#include "Military/Interfaces/Observables/UnitsCollectionCreationObservable.h"
#include "UnitsFactory.generated.h"

UCLASS()
class UUnitsFactory : public UWorldSubsystem, public IUnitsCreationObservable, public IUnitRemovalObservable, public IUnitsCollectionCreationObservable
{
	GENERATED_BODY()
public:
	virtual UUnit* CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag);
	
	virtual void Remove(UUnit* Unit);
};

// TODO: Add remove logic in destructor 
