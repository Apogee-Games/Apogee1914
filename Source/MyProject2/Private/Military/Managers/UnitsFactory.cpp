
#include "Military/Managers/UnitsFactory.h"

#include "Administration/Managers/CountriesManager.h"
#include "Military/Instances/Units/BranchUnits/Division.h"
#include "Military/Instances/Units/BranchUnits/Flight.h"
#include "Military/Instances/Units/BranchUnits/Squadron.h"

inline TMap<FName, TSubclassOf<UUnit>> MilitaryBranchUnitsTypes = {
	{"Army", UDivision::StaticClass()},
	{"Navy", USquadron::StaticClass()},
	{"AirForce", UFlight::StaticClass()}
};

UUnit* UUnitsFactory::CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag)
{
	// TODO: Add some logic for delay
	//TODO: Error checks ?

	UUnit* Unit = NewObject<UUnit>(GetWorld(), MilitaryBranchUnitsTypes[Description->MilitaryBranch]);
	UCountry* CountryOwner = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(CountryOwnerTag);
	Unit->Init(Description, Province, CountryOwner);
	NotifyUnitCreation(Unit);
	return Unit;
}

void UUnitsFactory::Remove(UUnit* Unit)
{
	NotifyUnitRemoval(Unit);
	delete Unit;
} 