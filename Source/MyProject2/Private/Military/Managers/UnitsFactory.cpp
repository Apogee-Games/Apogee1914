
#include "Military/Managers/UnitsFactory.h"

#include "Administration/Managers/CountriesManager.h"
#include "Military/Instances/Units/BranchUnits/Division.h"
#include "Military/Instances/Units/BranchUnits/Flight.h"
#include "Military/Instances/Units/BranchUnits/Squadron.h"

UUnit* UUnitsFactory::Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag)
{
	UUnit* Unit = CreateUnit(Description, Province, CountryOwnerTag);
	// TODO: Add some logic for delay
	NotifyUnitCreation(Unit);
	return Unit;
}

UUnit* UUnitsFactory::CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag) const
{
	UUnit* Unit = nullptr; // TODO: Check reflection C++ or C# to use here
	UCountry* CountryOwner = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(CountryOwnerTag);
	if (Description->MilitaryBranch == "Army")
	{
		Unit = NewObject<UDivision>();
	} else if (Description->MilitaryBranch == "Navy")
	{
		Unit = NewObject<USquadron>();
	} else if (Description->MilitaryBranch == "AirForce")
	{
		Unit = NewObject<UFlight>();
	}
	if (Unit)
	{
		Unit->Init(Description, Province, CountryOwner);
	}
	return Unit;
}

void UUnitsFactory::Remove(UUnit* Unit)
{
	NotifyUnitRemoval(Unit);
	delete Unit;
} 