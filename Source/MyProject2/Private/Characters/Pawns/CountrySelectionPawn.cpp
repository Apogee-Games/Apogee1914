#include "Characters/Pawns/CountrySelectionPawn.h"

#include "MyGameInstance.h"
#include "Characters/StateMachine/CountrySelectionPawnState.h"

void ACountrySelectionPawn::BeginPlay()
{
	Super::BeginPlay();

	SetPawnState(FCountrySelectionPawnState::GetInstance());
}
