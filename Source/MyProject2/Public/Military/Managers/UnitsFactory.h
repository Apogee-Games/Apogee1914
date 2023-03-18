#pragma once
#include "Military/Instances/Units/BranchUnits/Division.h"
#include "Military/Instances/Units/BranchUnits/Flight.h"
#include "Military/Instances/Units/BranchUnits/Squadron.h"

class UUnit;


#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "Military/Interfaces/Observables/UnitCreationObservable.h"
#include "Military/Interfaces/Observables/UnitRemovalObservable.h"
#include "Military/Interfaces/Observables/UnitsCollectionGroupCreationObservable.h"
#include "Military/Interfaces/Observables/UnitsCollectionCreationObservable.h"
#include "Military/Interfaces/Observables/UnitsCollectionRemovalObservable.h"
#include "Military/Interfaces/Observables/UnitsCollectionGroupRemovalObservable.h"
#include "UnitsFactory.generated.h"

UCLASS()
class UUnitsFactory : public UWorldSubsystem, public IUnitsCreationObservable, public IUnitRemovalObservable, public IUnitsCollectionCreationObservable, public IUnitsCollectionGroupCreationObservable,public IUnitsCollectionRemovalObservable, public IUnitsCollectionGroupRemovalObservable
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UUnit* CreateUnit(const FUnitDescription* Description, UProvince* Province);
	
	UUnit* CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag);

	UUnitsCollection* CreateUnitCollection(EMilitaryBranch MilitaryBranch, UCountry* CountryOwner);

	UUnitsCollectionGroup* CreateUnitCollectionGroup(EMilitaryBranch MilitaryBranch, UCountry* CountryOwner);
	
	void RemoveUnit(UUnit* Unit);

	void RemoveUnitCollection(UUnitsCollection* UnitsCollection);

	void RemoveUnitCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);
private:
	inline static TMap<FName, TSubclassOf<UUnit>> MilitaryBranchUnitsTypes = {
		{"Army", UDivision::StaticClass()},
		{"Navy", USquadron::StaticClass()},
		{"AirForce", UFlight::StaticClass()}
	};
};

// TODO: Add remove logic in destructor 
