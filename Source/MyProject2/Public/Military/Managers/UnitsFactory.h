#pragma once
#include "Scenario.h"
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
class UUnitsFactory : public UGameInstanceSubsystem, public IUnitsCreationObservable, public IUnitRemovalObservable, public IUnitsCollectionCreationObservable, public IUnitsCollectionGroupCreationObservable,public IUnitsCollectionRemovalObservable, public IUnitsCollectionGroupRemovalObservable
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);

	UUnit* CreateUnit(const FUnitDescription* Description, UProvince* Province);
	
	UUnit* CreateUnit(const FUnitDescription* Description, UProvince* Province, const FName& CountryOwnerTag);

	UUnitsCollection* CreateUnitCollection(EMilitaryBranch MilitaryBranch, UCountry* CountryOwner, const TArray<UUnit*>& UnitsToAdd);
	
	UUnitsCollection* CreateUnitCollection(EMilitaryBranch MilitaryBranch, UCountry* CountryOwner);

	UUnitsCollectionGroup* CreateUnitCollectionGroup(EMilitaryBranch MilitaryBranch, UCountry* CountryOwner, const TArray<UUnitsCollection*>& UnitsCollectionsToAdd);
		
	UUnitsCollectionGroup* CreateUnitCollectionGroup(EMilitaryBranch MilitaryBranch, UCountry* CountryOwner);

	void RemoveUnits(const TArray<UUnit*>& UnitsToRemove, bool IsClearing = false);
	
	void RemoveUnit(UUnit* Unit, bool IsClearing = false);

	void RemoveUnitCollection(UUnitsCollection* UnitsCollection, bool IsClearing = false);

	void RemoveUnitCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup, bool IsClearing = false);
private:
	UPROPERTY()
	TArray<UUnit*> Units;

	UPROPERTY()
	TArray<UUnitsCollection*> UnitsCollections;
	
	UPROPERTY()
	TArray<UUnitsCollectionGroup*> UnitsCollectionGroups;
	
	void Clear();

	void Init(UScenario* Scenario);

	// Need Unit types, Military branch
	
	inline static TMap<FName, TSubclassOf<UUnit>> MilitaryBranchUnitsTypes = {
		{"Army", UDivision::StaticClass()},
		{"Navy", USquadron::StaticClass()},
		{"AirForce", UFlight::StaticClass()}
	};
};

// TODO: Add remove logic in destructor 
