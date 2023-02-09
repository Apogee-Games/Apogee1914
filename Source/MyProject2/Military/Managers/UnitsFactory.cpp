#include "UnitsFactory.h"

UUnit* UUnitsFactory::Create(FUnitDescription* Description, const FColor& Position, const FString& CountryOwnerTag, UUnitsRenderer* Renderer)
{
	// TODO: Add some logic for delay
	UUnit* Unit = NewObject<UUnit>(GetWorld());
	Unit->Init(Description, Position, CountryOwnerTag, Renderer);
	NotifyUnitCreation(Unit);
	return Unit;
}

void UUnitsFactory::Remove(UUnit* Unit)
{
	NotifyUnitRemoval(Unit);
	delete Unit;
}