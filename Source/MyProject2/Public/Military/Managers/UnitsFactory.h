#pragma once
#include "Scenario.h"
#include "Interfaces/BaseManager.h"

class UUnit;
class UUnitsCollection;
class UUnitsCollectionGroup;

UENUM()
enum class EUnitStatus
{
	Formed,
	Dissolved
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUnitStatusChanged, UUnit*, EUnitStatus)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUnitsCollectionStatusChanged, UUnitsCollection*, EUnitStatus)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUnitsCollectionGroupStatusChanged, UUnitsCollectionGroup*, EUnitStatus)


#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "UnitsFactory.generated.h"

UCLASS()
class UUnitsFactory : public UBaseManager
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
	
	FOnUnitStatusChanged OnUnitStatusChanged;
	FOnUnitsCollectionStatusChanged OnUnitsCollectionStatusChanged;
	FOnUnitsCollectionGroupStatusChanged OnUnitsCollectionGroupStatusChanged;
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
