#pragma once
#include "Military/Instances/Units/BranchUnits/Division.h"
#include "Military/Instances/Units/BranchUnits/Flight.h"
#include "Military/Instances/Units/BranchUnits/Squadron.h"

class UUnit;

#include "Military/Interfaces/Observables/UnitsCollectionGroupCreationObservable.h"
#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "Military/Interfaces/Observables/UnitCreationObservable.h"
#include "Military/Interfaces/Observables/UnitRemovalObservable.h"
#include "Military/Interfaces/Observables/UnitsCollectionCreationObservable.h"
#include "UnitsFactory.generated.h"

UCLASS()
class UUnitsFactory : public UWorldSubsystem, public IUnitsCreationObservable, public IUnitRemovalObservable, public IUnitsCollectionCreationObservable, public IUnitsCollectionGroupCreationObservable
{
	GENERATED_BODY()
public:
	virtual UUnit* CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag);

	virtual UUnitsCollection* CreateUnitCollection(EMilitaryBranch MilitaryBranch);

	virtual UUnitsCollectionGroup* CreateUnitCollectionGroup(EMilitaryBranch MilitaryBranch);
	
	virtual void Remove(UUnit* Unit);
private:
	
	inline static TMap<FName, TSubclassOf<UUnit>> MilitaryBranchUnitsTypes = {
		{"Army", UDivision::StaticClass()},
		{"Navy", USquadron::StaticClass()},
		{"AirForce", UFlight::StaticClass()}
	};

};

// TODO: Add remove logic in destructor 
