#pragma once
#include "Military/Descriptions/UnitDescription.h"
#include "UnitsRenderer.h"
#include "Military/Interfaces/Observables/UnitCreationObservable.h"
#include "Military/Interfaces/Observables/UnitRemovalObservable.h"
#include "UnitsFactory.generated.h"


UCLASS()
class UUnitsFactory : public UWorldSubsystem, public IUnitCreationObservable, public IUnitRemovalObservable
{
	GENERATED_BODY()
public:
	
	virtual UUnit* Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag);
	
	virtual void Remove(UUnit* Unit);

private:
	UUnit* CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag) const;
};


// TODO: Add remove logic in destructor 
