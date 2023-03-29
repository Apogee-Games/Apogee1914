#include "Characters/Components/UnitsSelectionComponent.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MilitaryControlPawnState.h"

// TODO: add logic to use military branches during selection

void UUnitsSelectionComponent::SelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool AddToExisting)
{
	UpdatePawnState();
	
	ClearSelectionIfNeeded(AddToExisting);

	RemoveUnitsSelectedByUnitsCollectionGroup(UnitsCollectionGroup);

	SelectedUnitsCollectionGroups.Add(UnitsCollectionGroup);

	SelectedUnitsWereUpdated();
}

void UUnitsSelectionComponent::SelectUnits(UUnitsCollection* UnitsCollection, bool AddToExisting)
{
	UpdatePawnState();

	ClearSelectionIfNeeded(AddToExisting);
	
	RemoveUnitsSelectedByUnitsCollection(UnitsCollection);

	SelectedUnitsCollections.Add(UnitsCollection);

	SelectedUnitsWereUpdated();
}

void UUnitsSelectionComponent::SelectUnits(const TArray<UUnit*>& Units, bool AddToExisting)
{
	UpdatePawnState();
	
	ClearSelectionIfNeeded(AddToExisting);
		
	for (const auto& Unit: Units)
	{
		SelectedUnits.Add(Unit);
	}
	
	SelectedUnitsWereUpdated();
}

void UUnitsSelectionComponent::SelectUnit(UUnit* Unit, bool AddToExisting)
{
	UpdatePawnState();

	ClearSelectionIfNeeded(AddToExisting);

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

void UUnitsSelectionComponent::UnSelectUnits(UUnitsCollection* UnitsCollection, bool NotifyAboutUpdate)
{
	SelectedUnitsCollections.Remove(UnitsCollection);
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::UnSelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool NotifyAboutUpdate)
{
	SelectedUnitsCollectionGroups.Remove(UnitsCollectionGroup);
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::SelectedUnitsWereUpdated() const
{
	APlayerController* PlayerController = GetOwner<AHumanPlayerPawn>()->GetController<APlayerController>();
	AHumanPlayerHUD* HUD = PlayerController->GetHUD<AHumanPlayerHUD>();
	HUD->GetUnitInstancesListDescriptionWidget()->SetSelectedUnits(SelectedUnits);
	HUD->GetUnitInstancesListDescriptionWidget()->SetSelectedUnits(SelectedUnitsCollections);
	HUD->GetUnitInstancesListDescriptionWidget()->SetSelectedUnits(SelectedUnitsCollectionGroups);
	// TODO: Think if it worth to add logic for separation adding units to selection or making new selection :) 
}

void UUnitsSelectionComponent::UpdatePawnState() const
{
	GetOwner<AHumanPlayerPawn>()->SetPawnState(FMilitaryControlPawnState::GetInstance());
}

void UUnitsSelectionComponent::ClearSelectionIfNeeded(bool AddToExisting)
{
	if (GetOwner<AHumanPlayerPawn>()->IsShiftPressed() || AddToExisting) return; // TODO: Do I need Shift here now? 

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