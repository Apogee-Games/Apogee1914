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
	UUnitsSelectionComponent();
	
	void SelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool AddToExisting = false);
	
	void SelectUnits(UUnitsCollection* UnitsCollection, bool AddToExisting = false);
	
	void SelectUnits(const TArray<UUnit*>& Units, bool AddToExisting = false);

	void SelectUnit(UUnit* Unit, bool AddToExisting = false);

	void ClearSelectedUnits();

	const TArray<FUnitsSelection>& GetUnitsSelectionsByBranch() const;
	
	void UnSelectUnits(UUnitsCollection* UnitsCollection, bool NotifyAboutUpdate = false);

	void UnSelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool NotifyAboutUpdate = false);

	bool HasSelectedUnits() const;
private:
	UPROPERTY()
	TArray<FUnitsSelection> Selections;

	void SelectedUnitsWereUpdated() const;

	void UpdatePawnState() const;

	void ClearSelectionIfNeeded(bool AddToExisting = false);

	void RemoveUnitsSelectedByUnitsCollection(UUnitsCollection* UnitsCollection);

	void RemoveUnitsSelectedByUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);

};