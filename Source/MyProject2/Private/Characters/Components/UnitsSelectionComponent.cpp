#include "Characters/Components/UnitsSelectionComponent.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MilitaryControlPawnState.h"
#include "Military/Descriptions/MilitaryBranchDescription.h"
#include "Military/Managers/UnitsFactory.h"

void UUnitsSelectionComponent::BeginPlay()
{
	const TArray<UMilitaryBranchDescription*> MilitaryBranches = GetWorld()->GetGameInstance()->GetSubsystem<UUnitsFactory>()->GetMilitaryBranches();
	for (auto& MilitaryBranch: MilitaryBranches)
	{
		FUnitsSelection Selection;
		Selection.MilitaryBranch = MilitaryBranch;
		Selections.Add(MilitaryBranch, Selection);
	}
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
	for (auto& [MilitaryBranch, Selection]: Selections)
	{
		Selection.SelectedUnits.Empty();
		Selection.SelectedUnitsCollections.Empty();
		Selection.SelectedUnitsCollectionGroups.Empty();
	}

	SelectedUnitsWereUpdated();
}

const TMap<UMilitaryBranchDescription*, FUnitsSelection>& UUnitsSelectionComponent::GetUnitsSelectionsByBranch() const
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
	for (const auto& [MilitaryBranch, Selection]: Selections)
	{
		if (Selection.SelectedUnits.Num() || Selection.SelectedUnitsCollections.Num() || Selection.SelectedUnitsCollectionGroups.Num())
			return true;
	}
	return false;
}

void UUnitsSelectionComponent::SelectedUnitsWereUpdated() const
{
	if (OnSelectionUpdated.IsBound())
	{
		for (auto& [MilitaryBranch, Selection]: Selections) // TODO: Will be fixed soon :)
		{
			OnSelectionUpdated.Broadcast(Selection);
		}
	}
	// TODO: Think if it worth to add logic for separation adding units to selection or making new selection :) 
}

void UUnitsSelectionComponent::UpdatePawnState() const
{
	GetOwner<AHumanPlayerPawn>()->SetPawnState(FMilitaryControlPawnState::GetInstance());
}

void UUnitsSelectionComponent::ClearSelectionIfNeeded(bool AddToExisting)
{
	if (GetOwner<AHumanPlayerPawn>()->ShouldAppend() || AddToExisting) return; // TODO: Do I need Shift here now? 

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

	UMilitaryBranchDescription* MilitaryBranch = UnitsCollection->GetMilitaryBranch();
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
	UMilitaryBranchDescription* MilitaryBranch = UnitsCollectionGroup->GetMilitaryBranch();
	for (const auto UnitsCollection: UnitsCollectionGroup->GetAll()) {
		Selections[MilitaryBranch].SelectedUnitsCollections.Remove(UnitsCollection);
	}
}