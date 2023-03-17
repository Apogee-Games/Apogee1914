#pragma once
#include "Military/Instances/Units/Unit.h"
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"

#include "UnitsSelectionComponent.generated.h"

class AHumanPlayerPawn;

UCLASS()
class UUnitsSelectionComponent: public USceneComponent
{
	GENERATED_BODY()
public:
	void SelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup);
	
	void SelectUnits(UUnitsCollection* UnitsCollection);
	
	void SelectUnits(const TArray<UUnit*>& Units);

	void SelectUnit(UUnit* Unit);

	void ClearSelectedUnits();

	const TSet<UUnitsCollectionGroup*>& GetSelectedUnitsCollectionGroups() const;
	
	const TSet<UUnitsCollection*>& GetSelectedUnitsCollections() const;
	
	const TSet<UUnit*>& GetSelectedUnits() const;
private:
	UPROPERTY()
	TSet<UUnit*> SelectedUnits;

	UPROPERTY()
	TSet<UUnitsCollection*> SelectedUnitsCollections;

	UPROPERTY()
	TSet<UUnitsCollectionGroup*> SelectedUnitsCollectionGroups;

	void SelectedUnitsWereUpdated() const;

	void UpdatePawnState() const;

	void ClearSelectionIfNeeded();

	void RemoveUnitsSelectedByUnitsCollection(UUnitsCollection* UnitsCollection);

	void RemoveUnitsSelectedByUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup);

};