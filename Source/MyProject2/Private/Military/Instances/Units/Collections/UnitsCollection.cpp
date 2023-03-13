
#include "Military/Instances/Units/Collections/UnitsCollection.h"

bool UUnitsCollection::Add(UUnit* Unit)
{
	if (Unit->GetMilitaryBranch() != MilitaryBranch) return false;
	Units.Add(Unit);
	return true;
}

bool UUnitsCollection::Remove(UUnit* Unit)
{
	if (Unit->GetMilitaryBranch() != MilitaryBranch) return false;
	return Units.Remove(Unit) != 0;
}

const TArray<UUnit*>& UUnitsCollection::GetAll() const
{
	return Units;
}

int32 UUnitsCollection::GetSize() const
{
	return Units.Num();
}
