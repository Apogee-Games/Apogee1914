#pragma once
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
	virtual FUnit* Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag);
	
	virtual FUnit* Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag, UUnitsRenderer* Renderer);

	virtual void Remove(FUnit* Unit);

private:
	TArray<IUnitRemovalObserver> RemovalObservers;
};
// TODO: Add remove logic in destructor 