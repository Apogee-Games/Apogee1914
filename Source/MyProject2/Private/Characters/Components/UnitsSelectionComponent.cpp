#include "Characters/Components/UnitsSelectionComponent.h"

#include "Characters/HumanPlayerHUD.h"
#include "Characters/StateMachine/MilitaryControlPawnState.h"
#include "Characters/HumanPlayerPawn.h"

void UUnitsSelectionComponent::SelectUnits(const TArray<UUnit*>& Units)
{
	GetOwner<AHumanPlayerPawn>()->SetPawnState(FMilitaryControlPawnState::GetInstance());
	
	if (!GetOwner<AHumanPlayerPawn>()->IsShiftPressed())
	{
		SelectedUnits.Empty();
	}
	
	for (const auto& Unit: Units)
	{
		SelectedUnits.Add(Unit);
	}
	SelectedUnitsWereUpdated();
}

void UUnitsSelectionComponent::SelectUnit(UUnit* Unit)
{
	GetOwner<AHumanPlayerPawn>()->SetPawnState(FMilitaryControlPawnState::GetInstance());

	if (!GetOwner<AHumanPlayerPawn>()->IsShiftPressed())
	{
		SelectedUnits.Empty();
	}
	SelectedUnits.Add(Unit);
	SelectedUnitsWereUpdated();
	// TODO: Add check for controlled country
}

void UUnitsSelectionComponent::ClearSelectedUnits()
{
	SelectedUnits.Empty();
	SelectedUnitsWereUpdated();
}

const TArray<UUnit*>& UUnitsSelectionComponent::GetSelectedUnits() const
{
	return SelectedUnits;
}


void UUnitsSelectionComponent::SelectedUnitsWereUpdated() const
{
	APlayerController* PlayerController = GetOwner<AHumanPlayerPawn>()->GetController<APlayerController>();
	AHumanPlayerHUD* HUD = PlayerController->GetHUD<AHumanPlayerHUD>();
	HUD->GetUnitInstancesListDescriptionWidget()->SetSelectedUnits(SelectedUnits);
	// TODO: Think if it worth to add logic for separation adding units to selection or making new selection :) 
}

