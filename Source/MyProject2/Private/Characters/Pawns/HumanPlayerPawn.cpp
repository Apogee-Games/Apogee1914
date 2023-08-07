// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Pawns/HumanPlayerPawn.h"
#include "EngineUtils.h"
#include "JsonObjectConverter.h"
#include "Characters/HUDs//HumanPlayerHUD.h"
#include "Administration/Managers/CountriesManager.h"
#include "Characters/Components/PlaneMapActor.h"
#include "Characters/Components/PlayerMovementComponent.h"
#include "Characters/Components/UnitsSelectionComponent.h"
#include "Characters/StateMachine/BuildingCreationPawnState.h"
#include "Characters/StateMachine/CountryManagementPawnState.h"
#include "Characters/StateMachine/LawsBrowsingPawnState.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Characters/StateMachine/ProductionBrowsingPawnState.h"
#include "Characters/StateMachine/StorageBrowsingPawnState.h"
#include "Characters/StateMachine/SupplyBrowsingPawnState.h"
#include "Characters/StateMachine/UnitCreationPawnState.h"
#include "Components/AudioComponent.h"
#include "Military/Managers/UnitsFactory.h"
#include "MyProject2/MyProject2.h"
#include "Serialization/AsyncPackageLoader.h"

// Sets default values
AHumanPlayerPawn::AHumanPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	UnitSelectionComponent = CreateDefaultSubobject<UUnitsSelectionComponent>(TEXT("Units selection"));
	UnitSelectionComponent->SetupAttachment(RootComponent);
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio component"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AHumanPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	OnPawnStateChanged.AddUObject(this, &ThisClass::PawnStateChanged);
	OnPauseChanged.AddUObject(this, &ThisClass::PauseChanged);

	FGlobalUIDelegates::OnCountrySelected.AddUObject(this, &ThisClass::SelectCountry);
	FGlobalUIDelegates::OnProvinceSelected.AddUObject(this, &ThisClass::SelectProvince);
	
	SetPawnState(FMapBrowsingPawnState::GetInstance());
}

void AHumanPlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	FGlobalUIDelegates::OnCountrySelected.RemoveAll(this);
	FGlobalUIDelegates::OnProvinceSelected.RemoveAll(this);
}

void AHumanPlayerPawn::SetRuledCountry(UCountry* Country)
{
	RuledCountry = Country;
}

void AHumanPlayerPawn::SelectUnitDescription(UUnitDescription* UnitDescription)
{
	SelectedUnitDescription = UnitDescription;
}

void AHumanPlayerPawn::SelectBuildingDescription(UBuildingDescription* BuildingDescription)
{
	SelectedBuildingDescription = BuildingDescription;
}

void AHumanPlayerPawn::SetCommandable(ICommandable* Commandable)
{
	SelectedCommandable = Commandable;
}

ICommandable* AHumanPlayerPawn::GetSelectedCommandable() const
{
	return SelectedCommandable;
}

void AHumanPlayerPawn::AddToBeInvitedCountry(UCountry* Country)
{
	ToBeInvitedCountry.Add(Country);
	OnCountryToBeInvitedToAllianceStatusChanged.Broadcast(Country, EToBeInvitedCountryStatus::Added);
}

void AHumanPlayerPawn::RemoveToBeInvitedCountry(UCountry* Country)
{
	ToBeInvitedCountry.Remove(Country);
	OnCountryToBeInvitedToAllianceStatusChanged.Broadcast(Country, EToBeInvitedCountryStatus::Removed);
}

TArray<UCountry*>& AHumanPlayerPawn::GetToBeInvitedCountries()
{
	return ToBeInvitedCountry;
}

UUnitDescription* AHumanPlayerPawn::GetSelectedUnitDescription() const
{
	return SelectedUnitDescription;
}

UBuildingDescription* AHumanPlayerPawn::GetSelectedBuildingDescription() const
{
	return SelectedBuildingDescription;
}

const FName& AHumanPlayerPawn::GetRuledCountryTag() const
{
	return RuledCountry->GetTag();
}

UCountry* AHumanPlayerPawn::GetRuledCountry() const
{
	return RuledCountry;
}

void AHumanPlayerPawn::PawnStateChanged(TSharedPtr<FPawnState> NewPawnState)
{
	if (AHumanPlayerHUD* HUD = GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>())
	{
		HUD->UpdateWidgetsVisibility();
	}
}

void AHumanPlayerPawn::PauseChanged(bool InbIsPaused)
{
	if (InbIsPaused)
	{
		GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetMenuWidget()->AddToPlayerScreen(1000);
	}
	else
	{
		GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetMenuWidget()->RemoveFromParent();
	}
}

// Called to bind functionality to input
void AHumanPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("UKey"), IE_Pressed, this, &AHumanPlayerPawn::SwitchState<FUnitCreationPawnState>);
	PlayerInputComponent->BindAction(TEXT("SKey"), IE_Pressed, this, &AHumanPlayerPawn::SwitchState<FStorageBrowsingPawnState>);
	PlayerInputComponent->BindAction(TEXT("PKey"), IE_Pressed, this, &AHumanPlayerPawn::SwitchState<FMapBrowsingPawnState>);
	PlayerInputComponent->BindAction(TEXT("BKey"), IE_Pressed, this, &AHumanPlayerPawn::SwitchState<FBuildingCreationPawnState>);
	PlayerInputComponent->BindAction(TEXT("Menu"), IE_Pressed, this, &AHumanPlayerPawn::SwitchPause);
}

void AHumanPlayerPawn::Play(USoundBase* Song)
{
	AudioComponent->SetSound(Song);
	AudioComponent->SetPaused(false);
	AudioComponent->Play();
}

void AHumanPlayerPawn::SetIsAudioPaused(bool IsAudioPaused)
{
	AudioComponent->SetPaused(IsAudioPaused);
}

void AHumanPlayerPawn::SetProductionSelectionFactory(UFactoryBuilding* Factory)
{
	SelectedFactory = Factory;
}

UFactoryBuilding* AHumanPlayerPawn::GetSelectedFactory() const
{
	return SelectedFactory;
}

void AHumanPlayerPawn::SelectWar(UWar* War)
{
	SelectedWar = War;
	OnWarSelected.Broadcast(War);
}

void AHumanPlayerPawn::SelectCountry(UCountry* Country)
{
	SelectedCountry = Country;
}

void AHumanPlayerPawn::SelectProvince(UProvince* Province)
{
	SelectedProvince = Province;
}

UWar* AHumanPlayerPawn::GetSelectedWar()
{
	return SelectedWar;
}

UCountry* AHumanPlayerPawn::GetSelectedCountry()
{
	return SelectedCountry;
}

UProvince* AHumanPlayerPawn::GetSelectedProvince()
{
	return SelectedProvince;
}
