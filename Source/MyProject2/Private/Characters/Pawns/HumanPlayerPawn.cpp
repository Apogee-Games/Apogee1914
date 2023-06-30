// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Pawns/HumanPlayerPawn.h"
#include "EngineUtils.h"
#include "JsonObjectConverter.h"
#include "Characters/HUDs//HumanPlayerHUD.h"
#include "Administration/Managers/CountriesManager.h"
#include "Characters/Components/PlaneMapActor.h"
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
#include "Serialization/AsyncPackageLoader.h"

// Sets default values
AHumanPlayerPawn::AHumanPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);

	UnitSelectionComponent = CreateDefaultSubobject<UUnitsSelectionComponent>(TEXT("Units selection"));
	UnitSelectionComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Movement component"));
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio component"));
	
	AudioComponent->SetupAttachment(RootComponent);
}

void AHumanPlayerPawn::SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState)
{
	if (PawnState == ProvidedPawnState) return;
	PawnState = ProvidedPawnState;
	GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>()->UpdateWidgetsVisibility();
}

void AHumanPlayerPawn::SetRuledCountry(UCountry* Country)
{
	RuledCountry = Country;
}

TSharedPtr<FPawnState> AHumanPlayerPawn::GetPawnState() const
{
	return PawnState;
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

void AHumanPlayerPawn::LeftClick()
{
	if (IsPaused) return;
	SetPawnState(PawnState->LeftClick(this));
}

void AHumanPlayerPawn::RightClick()
{
	if (IsPaused) return;
	SetPawnState(PawnState->RightClick(this));
}

void AHumanPlayerPawn::ShiftPressed()
{
	bIsShiftPressed = true;
}

// Called when the game starts or when spawned
void AHumanPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (!MapActor)
	{
		InitMapActor();
	}
	
	SetPawnState(FMapBrowsingPawnState::GetInstance());
}

void AHumanPlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

bool AHumanPlayerPawn::IsShiftPressed() const
{
	return bIsShiftPressed;
}

void AHumanPlayerPawn::Pause()
{
	IsPaused = true;
	GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetMenuWidget()->AddToPlayerScreen(1000);
}

void AHumanPlayerPawn::UnPause()
{
	IsPaused = false;
	GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetMenuWidget()->RemoveFromViewport();
}

void AHumanPlayerPawn::SwitchPause()
{
	//TODO: Add logic to stop time if in single player mode :)
	if (IsPaused) 
	{
		UnPause();
	} else
	{
		Pause();
	}
}

void AHumanPlayerPawn::InitMapActor()
{
	MapActor = Cast<AMapActor>(GetWorld()->SpawnActor(MapActorClass));
	MovementComponent->Init(MapActor);
}

// Called every frame
void AHumanPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsPaused) return;
	MovementComponent->Move(DeltaTime);
}

void AHumanPlayerPawn::ShiftReleased()
{
	bIsShiftPressed = false;
}

void AHumanPlayerPawn::SwitchUnitCreationState()
{
	if (IsPaused) return;
	if (PawnState == FUnitCreationPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FUnitCreationPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SwitchStorageBrowsingState()
{
	if (IsPaused) return;
	if (PawnState == FStorageBrowsingPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FStorageBrowsingPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SwitchSupplyBrowsingState()
{
	if (IsPaused) return;
	if (PawnState == FSupplyBrowsingPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FSupplyBrowsingPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SwitchBuildingCreationState()
{
	if (IsPaused) return;
	if (PawnState == FBuildingCreationPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FBuildingCreationPawnState::GetInstance());
	}
}

// Called to bind functionality to input
void AHumanPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), MovementComponent, &UPlayerMovementComponent::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Right"), MovementComponent, &UPlayerMovementComponent::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Scroll"), MovementComponent, &UPlayerMovementComponent::Scroll);
	PlayerInputComponent->BindAction(TEXT("LeftClick"), IE_Pressed, this, &AHumanPlayerPawn::LeftClick);
	PlayerInputComponent->BindAction(TEXT("RightClick"), IE_Pressed, this, &AHumanPlayerPawn::RightClick);
	PlayerInputComponent->BindAction(TEXT("Shift"), IE_Pressed, this, &AHumanPlayerPawn::ShiftPressed);
	PlayerInputComponent->BindAction(TEXT("Shift"), IE_Released, this, &AHumanPlayerPawn::ShiftReleased);
	PlayerInputComponent->BindAction(TEXT("UKey"), IE_Pressed, this, &AHumanPlayerPawn::SwitchUnitCreationState);
	PlayerInputComponent->BindAction(TEXT("SKey"), IE_Pressed, this, &AHumanPlayerPawn::SwitchStorageBrowsingState);
	PlayerInputComponent->BindAction(TEXT("PKey"), IE_Pressed, this, &AHumanPlayerPawn::SwitchSupplyBrowsingState);
	PlayerInputComponent->BindAction(TEXT("BKey"), IE_Pressed, this, &AHumanPlayerPawn::SwitchBuildingCreationState);
	PlayerInputComponent->BindAction(TEXT("Menu"), IE_Pressed, this, &AHumanPlayerPawn::SwitchPause);
}

void AHumanPlayerPawn::SwitchCountryManagementState()
{
	if (IsPaused) return;
	if (PawnState == FCountryManagementPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FCountryManagementPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SwitchLawsBrowsingState()
{
	if (IsPaused) return;
	if (PawnState == FLawsBrowsingPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FLawsBrowsingPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SwitchProductionBrowsingState()
{
	if (IsPaused) return;
	if (PawnState == FProductionBrowsingPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FProductionBrowsingPawnState::GetInstance());
	}
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

AMapActor* AHumanPlayerPawn::GetMapActor()
{
	if (!MapActor)
	{
		InitMapActor();
	}
	return MapActor;
}
