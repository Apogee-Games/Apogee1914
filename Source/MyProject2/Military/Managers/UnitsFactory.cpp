#include "UnitsFactory.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Military/Instances/Units/BranchUnits/Division.h"
#include "MyProject2/Military/Instances/Units/BranchUnits/Flight.h"
#include "MyProject2/Military/Instances/Units/BranchUnits/Squadron.h"

FUnit* UUnitsFactory::Create(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag)
{
	FUnit* Unit = CreateUnit(Description, Province, CountryOwnerTag);
	// TODO: Add some logic for delay
	NotifyUnitCreation(Unit);
	return Unit;
}

FUnit* UUnitsFactory::CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag) const
{
	FUnit* Unit = nullptr; // TODO: Check reflection C++ or C# to use here
	UCountry* CountryOwner = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(CountryOwnerTag);
	if (Description->MilitaryBranch == "Army")
	{
		Unit = new FDivision(Description, Province, CountryOwner);
	} else if (Description->MilitaryBranch == "Navy")
	{
		Unit = new FSquadron(Description, Province, CountryOwner);
	} else if (Description->MilitaryBranch == "AirForce")
	{
		Unit = new FFlight(Description, Province, CountryOwner); 
	}
	return Unit;
}

void UUnitsFactory::Remove(FUnit* Unit)
{
	NotifyUnitRemoval(Unit);
	delete Unit;
} 