
#include "Widgets/Military/Carriers/UnitsListCarrier.h"

void UUnitsListCarrier::AddUnit(UUnit* Unit)
{
	Units.Add(Unit);
}

void UUnitsListCarrier::RemoveUnit(UUnit* Unit)
{
		Units.Remove(Unit);
}

bool UUnitsListCarrier::IsEmpty() const
{
	return Units.IsEmpty();
}

int32 UUnitsListCarrier::Num() const
{
	return Units.Num();
}

UUnit* UUnitsListCarrier::GetFirst() const
{
	return Units.IsEmpty() ? nullptr : Units[0];
}

const TArray<UUnit*>& UUnitsListCarrier::GetUnits() const
{
	return Units;
}
