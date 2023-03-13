#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"

bool UUnitsCollectionGroup::Add(UUnitsCollection* Collection)
{
	if (Collection->GetMilitaryBranch() != MilitaryBranch) return false;
	Collections.Add(Collection);
	return true;
}

bool UUnitsCollectionGroup::Remove(UUnitsCollection* Collection)
{
	if (Collection->GetMilitaryBranch() != MilitaryBranch) return false;
	return Collections.Remove(Collection) != 0;
}

const TArray<UUnitsCollection*>& UUnitsCollectionGroup::GetAll() const
{
	return Collections;
}

int32 UUnitsCollectionGroup::GetSize() const
{
	return Collections.Num();
}
