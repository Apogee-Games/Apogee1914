#pragma once
#include "Military/Instances/Units/Unit.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"

#include "UnitsSelectionComponent.generated.h"

class AHumanPlayerPawn;

USTRUCT()
struct FUnitsSelection
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<UUnit*> SelectedUnits;
	
	UPROPERTY()
	TSet<UUnitsCollection*> SelectedUnitsCollections;

	UPROPERTY()
	TSet<UUnitsCollectionGroup*> SelectedUnitsCollectionGroups;

	bool IsEmpty() const
	{
		return SelectedUnits.IsEmpty() && SelectedUnitsCollections.IsEmpty() && SelectedUnitsCollectionGroups.IsEmpty();
	}
};

UCLASS()
class UUnitsSelectionComponent: public USceneComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	void SelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool NotifyAboutUpdate = true, bool AddToExisting = false);

	void SelectUnits(const TSet<UUnitsCollection*>& UnitsCollections, bool NotifyAboutUpdate = true, bool AddToExisting = false);
	
	void SelectUnits(const TArray<UUnitsCollection*>& UnitsCollections, bool NotifyAboutUpdate = true, bool AddToExisting = false);

	void SelectUnits(UUnitsCollection* UnitsCollection, bool NotifyAboutUpdate = true, bool AddToExisting = false);
	
	void SelectUnits(const TArray<UUnit*>& Units, bool NotifyAboutUpdate = true, bool AddToExisting = false);

	void SelectUnits(const TSet<UUnit*>& Units, bool NotifyAboutUpdate = true, bool AddToExisting = false); // TODO: Templates ?

	void SelectUnit(UUnit* Unit, bool NotifyAboutUpdate = true, bool AddToExisting = false);

	void ClearSelectedUnits();

	const TMap<UMilitaryBranchDescription*, FUnitsSelection>& GetUnitsSelectionsByBranch() const;
	
	void UnSelectUnits(const TArray<UUnitsCollection*>& UnitsCollections, bool NotifyAboutUpdate = false);
	
	void UnSelectUnits(UUnitsCollection* UnitsCollection, bool NotifyAboutUpdate = false);
	
	void UnSelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool NotifyAboutUpdate = false);

	void UnSelectUnits(const TArray<UUnit*>& Units, bool NotifyAboutUpdate = false);
	
	void UnSelectUnit(UUnit* Unit, bool NotifyAboutUpdate = false);
	
	bool HasSelectedUnits() const;
private:
	UPROPERTY()
	TMap<UMilitaryBranchDescription*, FUnitsSelection> Selections;

	void SelectedUnitsWereUpdated() const;

	void UpdatePawnState() const;

	void ClearSelectionIfNeeded(bool AddToExisting = false);

	void RemoveUnitsSelectedByUnitsCollection(UUnitsCollection* UnitsCollection);

	void RemoveUnitsSelectedByUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);
};