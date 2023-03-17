// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Pawns/HumanPlayerPawn.h"
#include "EngineUtils.h"
#include "Characters/HUDs//HumanPlayerHUD.h"
#include "Administration/Managers/CountriesManager.h"
#include "Characters/Components/PlaneMapActor.h"
#include "Characters/Components/UnitsSelectionComponent.h"
#include "Characters/StateMachine/BuildingCreationPawnState.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Characters/StateMachine/StorageBrowsingPawnState.h"
#include "Characters/StateMachine/SupplyBrowsingPawnState.h"
#include "Characters/StateMachine/UnitCreationPawnState.h"

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
}

void AHumanPlayerPawn::SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState)
{
	if (PawnState == ProvidedPawnState) return;
	PawnState = ProvidedPawnState;
	GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>()->UpdateWidgetsVisibility();
}

void AHumanPlayerPawn::SetRuledCountryTag(const FName& NewRuledCountryTag)
{
	RuledCountry = GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry(NewRuledCountryTag);
}

TSharedPtr<FPawnState> AHumanPlayerPawn::GetPawnState() const
{
	return PawnState;
}

void AHumanPlayerPawn::SelectUnitDescription(const FUnitDescription* UnitDescription)
{
	SelectedUnitDescription = UnitDescription;
}

void AHumanPlayerPawn::SelectBuildingDescription(const FBuildingDescription* BuildingDescription)
{
	SelectedBuildingDescription = BuildingDescription;
}

const FUnitDescription* AHumanPlayerPawn::GetSelectedUnitDescription() const
{
	return SelectedUnitDescription;
}

const FBuildingDescription* AHumanPlayerPawn::GetSelectedBuildingDescription() const
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
	SetPawnState(PawnState->LeftClick(this));
}

void AHumanPlayerPawn::RightClick()
{
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

	MapActor = Cast<AMapActor>(GetWorld()->SpawnActor(MapActorClass));
	
	MovementComponent->Init(MapActor);
	
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

// Called every frame
void AHumanPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementComponent->Move(DeltaTime);
}

void AHumanPlayerPawn::ShiftReleased()
{
	bIsShiftPressed = false;
}

void AHumanPlayerPawn::SetUnitCreationState()
{
	if (PawnState == FUnitCreationPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FUnitCreationPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SetStorageBrowsingState()
{
	if (PawnState == FStorageBrowsingPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FStorageBrowsingPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SetSupplyBrowsingState()
{
	if (PawnState == FSupplyBrowsingPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	}
	else
	{
		SetPawnState(FSupplyBrowsingPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SetBuildingCreationState()
{
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
	PlayerInputComponent->BindAction(TEXT("UKey"), IE_Pressed, this, &AHumanPlayerPawn::SetUnitCreationState);
	PlayerInputComponent->BindAction(TEXT("SKey"), IE_Pressed, this, &AHumanPlayerPawn::SetStorageBrowsingState);
	PlayerInputComponent->BindAction(TEXT("PKey"), IE_Pressed, this, &AHumanPlayerPawn::SetSupplyBrowsingState);
	PlayerInputComponent->BindAction(TEXT("BKey"), IE_Pressed, this, &AHumanPlayerPawn::SetBuildingCreationState);
}