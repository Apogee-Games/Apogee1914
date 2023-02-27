#pragma once
#include "MyProject2/Military/Instances/Unit.h"
#include "MyProject2/Military/Descriptions/UnitDescription.h"
#include "UnitsRenderer.h"
#include "MyProject2/Military/Interfaces/Observables/UnitCreationObservable.h"
#include "MyProject2/Military/Interfaces/Observables/UnitRemovalObservable.h"
#include "UnitsFactory.generated.h"


UCLASS()
class UUnitsFactory : public UWorldSubsystem, public IUnitCreationObservable, public IUnitRemovalObservable
{
	GENERATED_BODY()
public:
	virtual UUnit* Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag);
	
	virtual UUnit* Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag, UUnitsRenderer* Renderer);

	virtual void Remove(UUnit* Unit);

private:
	TArray<IUnitRemovalObserver> RemovalObservers;
};
