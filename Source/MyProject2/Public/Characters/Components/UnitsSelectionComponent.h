#pragma once
#include "Military/Instances/Units/Unit.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"
#include "Widgets/Military/Selection/SelectedUnitsCollectionWidget.h"

#include "UnitsSelectionComponent.generated.h"

class AHumanPlayerPawn;

UCLASS()
class UUnitsSelectionComponent: public USceneComponent
{
	GENERATED_BODY()
public:
	void SelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool AddToExisting = false);
	
	void SelectUnits(UUnitsCollection* UnitsCollection, bool AddToExisting = false);
	
	void SelectUnits(const TArray<UUnit*>& Units, bool AddToExisting = false);

	void SelectUnit(UUnit* Unit, bool AddToExisting = false);

	void ClearSelectedUnits();

	const TSet<UUnitsCollectionGroup*>& GetSelectedUnitsCollectionGroups() const;
	
	const TSet<UUnitsCollection*>& GetSelectedUnitsCollections() const;
	
	const TSet<UUnit*>& GetSelectedUnits() const;
	
	void UnSelectUnits(UUnitsCollection* UnitsCollection, bool NotifyAboutUpdate = false);

	void UnSelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool NotifyAboutUpdate = false);
private:
	UPROPERTY()
	TSet<UUnit*> SelectedUnits;

	UPROPERTY()
	TSet<UUnitsCollection*> SelectedUnitsCollections;

	UPROPERTY()
	TSet<UUnitsCollectionGroup*> SelectedUnitsCollectionGroups;

	void SelectedUnitsWereUpdated() const;

	void UpdatePawnState() const;

	void ClearSelectionIfNeeded(bool AddToExisting = false);

	void RemoveUnitsSelectedByUnitsCollection(UUnitsCollection* UnitsCollection);

	void RemoveUnitsSelectedByUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);

};