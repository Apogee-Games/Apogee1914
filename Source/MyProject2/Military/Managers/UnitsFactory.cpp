#include "UnitsFactory.h"

UUnit* UUnitsFactory::Create(FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag, UUnitsRenderer* Renderer)
{
	// TODO: Add some logic for delay
	UUnit* Unit = NewObject<UUnit>(GetWorld());
	Unit->Init(Description, Province, CountryOwnerTag, Renderer);
	NotifyUnitCreation(Unit);
	return Unit;
}

void UUnitsFactory::Remove(UUnit* Unit)
{
	NotifyUnitRemoval(Unit);
	delete Unit;
}