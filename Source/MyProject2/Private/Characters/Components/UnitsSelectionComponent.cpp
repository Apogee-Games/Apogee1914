#include "Characters/Components/UnitsSelectionComponent.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MilitaryControlPawnState.h"

// TODO: add logic to use military branches during selection

UUnitsSelectionComponent::UUnitsSelectionComponent()
{
	Selections.SetNum(MilitaryBranchesNumber);	
}

void UUnitsSelectionComponent::SelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool NotifyAboutUpdate, bool AddToExisting)
{
	UpdatePawnState();
	
	ClearSelectionIfNeeded(AddToExisting);

	RemoveUnitsSelectedByUnitsCollectionGroup(UnitsCollectionGroup);

	Selections[UnitsCollectionGroup->GetMilitaryBranch()].SelectedUnitsCollectionGroups.Add(UnitsCollectionGroup);

	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::SelectUnits(const TSet<UUnitsCollection*>& UnitsCollections, bool NotifyAboutUpdate, bool AddToExisting)
{
	for (const auto& UnitsCollection: UnitsCollections)
	{
		SelectUnits(UnitsCollection, false, AddToExisting);		
	}
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::SelectUnits(const TArray<UUnitsCollection*>& UnitsCollections, bool NotifyAboutUpdate, bool AddToExisting)
{
	for (const auto& UnitsCollection: UnitsCollections)
	{
		SelectUnits(UnitsCollection, false, AddToExisting);		
	}
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::SelectUnits(UUnitsCollection* UnitsCollection, bool NotifyAboutUpdate, bool AddToExisting)
{
	UpdatePawnState();

	ClearSelectionIfNeeded(AddToExisting);
	
	RemoveUnitsSelectedByUnitsCollection(UnitsCollection);

	Selections[UnitsCollection->GetMilitaryBranch()].SelectedUnitsCollections.Add(UnitsCollection);

	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::SelectUnits(const TArray<UUnit*>& Units, bool NotifyAboutUpdate, bool AddToExisting)
{
	UpdatePawnState();
	
	ClearSelectionIfNeeded(AddToExisting);

	for (const auto& Unit: Units)
	{
		Selections[Unit->GetMilitaryBranch()].SelectedUnits.Add(Unit);
	}
	
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::SelectUnits(const TSet<UUnit*>& Units, bool NotifyAboutUpdate, bool AddToExisting)
{
	UpdatePawnState();
	
	ClearSelectionIfNeeded(AddToExisting);

	for (const auto& Unit: Units)
	{
		Selections[Unit->GetMilitaryBranch()].SelectedUnits.Add(Unit);
	}
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::SelectUnit(UUnit* Unit, bool NotifyAboutUpdate, bool AddToExisting)
{
	UpdatePawnState();

	ClearSelectionIfNeeded(AddToExisting);

	Selections[Unit->GetMilitaryBranch()].SelectedUnits.Add(Unit);
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::ClearSelectedUnits()
{
	for (auto& Selection: Selections)
	{
		Selection.SelectedUnits.Empty();
		Selection.SelectedUnitsCollections.Empty();
		Selection.SelectedUnitsCollectionGroups.Empty();
	}

	SelectedUnitsWereUpdated();
}

const TArray<FUnitsSelection>& UUnitsSelectionComponent::GetUnitsSelectionsByBranch() const
{
	return Selections;
}

void UUnitsSelectionComponent::UnSelectUnits(const TArray<UUnitsCollection*>& UnitsCollections, bool NotifyAboutUpdate)
{
	for (const auto& UnitsCollection: UnitsCollections)
	{
		Selections[UnitsCollection->GetMilitaryBranch()].SelectedUnitsCollections.Remove(UnitsCollection);
	}
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::UnSelectUnits(UUnitsCollection* UnitsCollection, bool NotifyAboutUpdate)
{
	Selections[UnitsCollection->GetMilitaryBranch()].SelectedUnitsCollections.Remove(UnitsCollection);
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::UnSelectUnits(UUnitsCollectionGroup* UnitsCollectionGroup, bool NotifyAboutUpdate)
{
	Selections[UnitsCollectionGroup->GetMilitaryBranch()].SelectedUnitsCollectionGroups.Remove(UnitsCollectionGroup);
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::UnSelectUnits(const TArray<UUnit*>& Units, bool NotifyAboutUpdate)
{
	for (const auto& Unit: Units)
	{
		Selections[Unit->GetMilitaryBranch()].SelectedUnits.Remove(Unit);
	}
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

void UUnitsSelectionComponent::UnSelectUnit(UUnit* Unit, bool NotifyAboutUpdate)
{
	Selections[Unit->GetMilitaryBranch()].SelectedUnits.Remove(Unit);
	if (NotifyAboutUpdate)
	{
		SelectedUnitsWereUpdated();
	}
}

bool UUnitsSelectionComponent::HasSelectedUnits() const
{
	for (const auto& Selection: Selections)
	{
		if (Selection.SelectedUnits.Num() || Selection.SelectedUnitsCollections.Num() || Selection.SelectedUnitsCollectionGroups.Num())
			return true;
	}
	return false;
}

void UUnitsSelectionComponent::SelectedUnitsWereUpdated() const
{
	APlayerController* PlayerController = GetOwner<AHumanPlayerPawn>()->GetController<APlayerController>();
	AHumanPlayerHUD* HUD = PlayerController->GetHUD<AHumanPlayerHUD>();
	HUD->GetUnitInstancesListDescriptionWidget()->SetSelections(Selections);
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
	
	for (const auto Unit: Selections[UnitsCollection->GetMilitaryBranch()].SelectedUnits)
	{
		if (UnitsCollection->Contains(Unit))
		{
			UnitsToClear.Add(Unit);
		}
	}

	int32 MilitaryBranch = UnitsCollection->GetMilitaryBranch();
	for (const auto Unit: UnitsToClear)
	{
		Selections[MilitaryBranch].SelectedUnits.Remove(Unit);
	}
}

void UUnitsSelectionComponent::RemoveUnitsSelectedByUnitsCollectionGroup(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	for (const auto UnitsCollection: UnitsCollectionGroup->GetAll())
	{
		RemoveUnitsSelectedByUnitsCollection(UnitsCollection);
	}
	int32 MilitaryBranch = UnitsCollectionGroup->GetMilitaryBranch();
	for (const auto UnitsCollection: UnitsCollectionGroup->GetAll()) {
		Selections[MilitaryBranch].SelectedUnitsCollections.Remove(UnitsCollection);
	}
}