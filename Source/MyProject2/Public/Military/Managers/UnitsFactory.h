#pragma once
#include "Scenario.h"
#include "Interfaces/BaseManager.h"
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
class UUnitsFactory : public UBaseManager, public IUnitsCreationObservable, public IUnitRemovalObservable, public IUnitsCollectionCreationObservable, public IUnitsCollectionGroupCreationObservable,public IUnitsCollectionRemovalObservable, public IUnitsCollectionGroupRemovalObservable
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;

	UUnit* CreateUnit(UUnitDescription* Description, UProvince* Province);
	
	UUnit* CreateUnit(UUnitDescription* Description, UProvince* Province, UCountryDescription* CountryDescription);

	UUnitsCollection* CreateUnitCollection(UMilitaryBranchDescription* MilitaryBranch, UCountry* CountryOwner, const TArray<UUnit*>& UnitsToAdd);
	
	UUnitsCollection* CreateUnitCollection(UMilitaryBranchDescription* MilitaryBranch, UCountry* CountryOwner);

	UUnitsCollectionGroup* CreateUnitCollectionGroup(UMilitaryBranchDescription* MilitaryBranch, UCountry* CountryOwner, const TArray<UUnitsCollection*>& UnitsCollectionsToAdd);
		
	UUnitsCollectionGroup* CreateUnitCollectionGroup(UMilitaryBranchDescription* MilitaryBranch, UCountry* CountryOwner);

	void RemoveUnits(const TArray<UUnit*>& UnitsToRemove, bool IsClearing = false);
	
	void RemoveUnit(UUnit* Unit, bool IsClearing = false);

	void RemoveUnitCollection(UUnitsCollection* UnitsCollection, bool IsClearing = false);

	void RemoveUnitCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup, bool IsClearing = false);

	const TArray<UMilitaryBranchDescription*>& GetMilitaryBranches() const;

	const TArray<UUnitDescription*>& GetUnitsDescriptions() const;

	const TArray<UUnit*>& GetUnits() const;

	virtual ELoadStage GetLoadStage() override;

	TArray<UUnit*> GetCountryControlledUnits(UCountry* Country);
private:
	UPROPERTY()
	TArray<UUnitDescription*> UnitDescriptions;

	UPROPERTY()
	TArray<UMilitaryBranchDescription*> MilitaryBranches;
	
	UPROPERTY()
	TArray<UUnit*> Units;

	UPROPERTY()
	TArray<UUnitsCollection*> UnitsCollections;
	
	UPROPERTY()
	TArray<UUnitsCollectionGroup*> UnitsCollectionGroups;
	
	void Clear();

	void Init(UScenario* Scenario);
};

// TODO: Add remove logic in destructor 
