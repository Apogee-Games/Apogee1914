#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"

bool UUnitsCollectionGroup::Add(UUnitsCollection* Collection)
{
	if (Collection->GetMilitaryBranch() != MilitaryBranch) return false;
	if (Collection->GetCountryController() != CountryController) return false;
	UUnitsCollectionGroup* CollectionGroup = Collection->GetUnitsCollectionGroup();
	if (CollectionGroup)
	{
		CollectionGroup->Remove(Collection);
	}
	Collections.Add(Collection);
	Collection->SetUnitsCollectionGroup(this);
	return true;
}

bool UUnitsCollectionGroup::Remove(UUnitsCollection* Collection)
{
	if (Collection->GetMilitaryBranch() != MilitaryBranch) return false;
 	if (Collection->GetCountryController() != CountryController) return false;
	Collection->SetUnitsCollectionGroup(nullptr);
	return Collections.Remove(Collection) != 0;
}

const TSet<UUnitsCollection*>& UUnitsCollectionGroup::GetAll() const
 {
	return Collections;
}

int32 UUnitsCollectionGroup::GetSize() const
{
	return Collections.Num();
}

bool UUnitsCollectionGroup::Contains(UUnitsCollection* Item)
{
	return Collections.Contains(Item);
}

void UUnitsCollectionGroup::ClearCollections()
{
	for (const auto& Collection: Collections)
	{
		Collection->SetUnitsCollectionGroup(nullptr);
	}
	Collections.Empty();
}
