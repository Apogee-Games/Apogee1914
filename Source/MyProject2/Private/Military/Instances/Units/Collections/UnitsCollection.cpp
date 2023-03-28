
#include "Military/Instances/Units/Collections/UnitsCollection.h"

bool UUnitsCollection::Add(UUnit* Unit)
{
	if (Unit->GetMilitaryBranch() != MilitaryBranch) return false;
	if (Unit->GetCountryController() != CountryController) return false;
	
	UUnitsCollection* PreviousUnitsCollection = Unit->GetUnitsCollection();
	if (PreviousUnitsCollection)
	{
		PreviousUnitsCollection->Remove(Unit);
	}
	
	Units.Add(Unit);
	Unit->SetUnitsCollection(this);
	return true;
}

bool UUnitsCollection::Remove(UUnit* Unit)
{
	if (Unit->GetMilitaryBranch() != MilitaryBranch) return false;
	if (Unit->GetCountryController() != CountryController) return false;
	Unit->SetUnitsCollection(nullptr);
	return Units.Remove(Unit) != 0;
}

const TSet<UUnit*>& UUnitsCollection::GetAll() const
{
	return Units;
}

int32 UUnitsCollection::GetSize() const
{
	return Units.Num();
}

bool UUnitsCollection::Contains(UUnit* Unit)
{
	return Units.Contains(Unit);
}
