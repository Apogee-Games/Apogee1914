#include "Characters/Components/UnitsSelectionComponent.h"

#include "Characters/HumanPlayerHUD.h"
#include "Characters/StateMachine/MilitaryControlPawnState.h"
#include "Characters/HumanPlayerPawn.h"

void UUnitsSelectionComponent::SelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	UpdatePawnState();
	
	ClearSelectionIfNeeded();

	RemoveUnitsSelectedByUnitsCollectionGroup(UnitsCollectionGroup);

	SelectedUnitsCollectionGroups.Add(UnitsCollectionGroup);

	SelectedUnitsWereUpdated();
}

void UUnitsSelectionComponent::SelectUnits(UUnitsCollection* UnitsCollection)
{
	UpdatePawnState();
	
	ClearSelectionIfNeeded();
	
	RemoveUnitsSelectedByUnitsCollection(UnitsCollection);

	SelectedUnitsCollections.Add(UnitsCollection);

	SelectedUnitsWereUpdated();
}

void UUnitsSelectionComponent::SelectUnits(const TArray<UUnit*>& Units)
{
	UpdatePawnState();
	
	ClearSelectionIfNeeded();
	
	for (const auto& Unit: Units)
	{
		SelectedUnits.Add(Unit);
	}
	
	SelectedUnitsWereUpdated();
}

void UUnitsSelectionComponent::SelectUnit(UUnit* Unit)
{
	UpdatePawnState();

	ClearSelectionIfNeeded();

	SelectedUnits.Add(Unit);

	SelectedUnitsWereUpdated();
	// TODO: Add check for controlled country
}

void UUnitsSelectionComponent::ClearSelectedUnits()
{
	SelectedUnits.Empty();

	SelectedUnitsCollections.Empty();

	SelectedUnitsCollectionGroups.Empty();

	SelectedUnitsWereUpdated();
}

const TSet<UUnitsCollectionGroup*>& UUnitsSelectionComponent::GetSelectedUnitsCollectionGroups() const
{
	return SelectedUnitsCollectionGroups;
}

const TSet<UUnitsCollection*>& UUnitsSelectionComponent::GetSelectedUnitsCollections() const
{
	return SelectedUnitsCollections;
}

const TSet<UUnit*>& UUnitsSelectionComponent::GetSelectedUnits() const
{
	return SelectedUnits;
}

void UUnitsSelectionComponent::SelectedUnitsWereUpdated() const
{
	APlayerController* PlayerController = GetOwner<AHumanPlayerPawn>()->GetController<APlayerController>();
	AHumanPlayerHUD* HUD = PlayerController->GetHUD<AHumanPlayerHUD>();
	HUD->GetUnitInstancesListDescriptionWidget()->SetSelectedUnits(SelectedUnits);
	// TODO: Set other selections :) 
	// TODO: Think if it worth to add logic for separation adding units to selection or making new selection :) 
}

void UUnitsSelectionComponent::UpdatePawnState() const
{
	GetOwner<AHumanPlayerPawn>()->SetPawnState(FMilitaryControlPawnState::GetInstance());
}

void UUnitsSelectionComponent::ClearSelectionIfNeeded()
{
	if (GetOwner<AHumanPlayerPawn>()->IsShiftPressed()) return;

	ClearSelectedUnits();
}

void UUnitsSelectionComponent::RemoveUnitsSelectedByUnitsCollection(UUnitsCollection* UnitsCollection)
{
	TArray<UUnit*> UnitsToClear;
	
	for (const auto Unit: SelectedUnits)
	{
		if (UnitsCollection->Contains(Unit))
		{
			UnitsToClear.Add(Unit);
		}
	}

	for (const auto Unit: UnitsToClear)
	{
		SelectedUnits.Remove(Unit);
	}
}

void UUnitsSelectionComponent::RemoveUnitsSelectedByUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	for (const auto UnitsCollection: UnitsCollectionGroup->GetAll())
	{
		RemoveUnitsSelectedByUnitsCollection(UnitsCollection);
	}

	for (const auto UnitsCollection: UnitsCollectionGroup->GetAll()) {
		SelectedUnitsCollections.Remove(UnitsCollection);
	}
}