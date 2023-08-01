// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Pawns/PlayablePawn.h"

#include "Camera/CameraComponent.h"
#include "Characters/Components/PlayerMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
APlayablePawn::APlayablePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	MovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Movement component"));
}

void APlayablePawn::SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState)
{
	if (PawnState != ProvidedPawnState)
	{
		PawnState = ProvidedPawnState;
	
		if (OnPawnStateChanged.IsBound()) {
			OnPawnStateChanged.Broadcast(PawnState);	
		}
	}
}

TSharedPtr<FPawnState> APlayablePawn::GetPawnState() const
{
	return PawnState;
}

// Called when the game starts or when spawned
void APlayablePawn::BeginPlay()
{
	Super::BeginPlay();
	
	MovementComponent->Init(GetMapActor());
}

// Called every frame
void APlayablePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovementComponent->Move(DeltaTime);
}

// Called to bind functionality to input
void APlayablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("LeftClick"), IE_Pressed, this, &ThisClass::LeftClick);
	PlayerInputComponent->BindAction(TEXT("RightClick"), IE_Pressed, this, &ThisClass::RightClick);

	PlayerInputComponent->BindAction(TEXT("Shift"), IE_Pressed, this, &ThisClass::ShouldAppendYes);
	PlayerInputComponent->BindAction(TEXT("Shift"), IE_Released, this, &ThisClass::ShouldAppendNo);

	PlayerInputComponent->BindAxis(TEXT("Forward"), MovementComponent, &UPlayerMovementComponent::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Right"), MovementComponent, &UPlayerMovementComponent::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Scroll"), MovementComponent, &UPlayerMovementComponent::Scroll);
}

void APlayablePawn::ShouldAppendYes()
{
	bShouldAppend = true;
}

void APlayablePawn::ShouldAppendNo()
{
	bShouldAppend = false;
}

void APlayablePawn::LeftClick()
{
	if (bIsPaused) return;
	SetPawnState(PawnState->LeftClick(this));
}

void APlayablePawn::RightClick()
{
	if (bIsPaused) return;
	SetPawnState(PawnState->RightClick(this));
}


void APlayablePawn::Pause()
{
	bIsPaused = true;
	if (OnPauseChanged.IsBound())
	{
		SetActorTickEnabled(false);
		OnPauseChanged.Broadcast(bIsPaused);
	}
}

void APlayablePawn::UnPause()
{
	bIsPaused = false;
	if (OnPauseChanged.IsBound())
	{
		SetActorTickEnabled(true);
		OnPauseChanged.Broadcast(bIsPaused);
	}
}

AMapActor* APlayablePawn::GetMapActor()
{
	if (!MapActor)
	{
		MapActor = GetWorld()->SpawnActor<AMapActor>(MapActorClass);
	}
	return MapActor;
}

bool APlayablePawn::ShouldAppend() const
{
	return bShouldAppend;
}

void APlayablePawn::SwitchPause()
{
	//TODO: Add logic to stop time if in single player mode :)
	if (bIsPaused) 
	{
		UnPause();
	} else
	{
		Pause();
	}
}


