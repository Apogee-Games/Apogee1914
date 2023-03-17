#include "Characters/Pawns/CountrySelectionPawn.h"

#include "MyGameInstance.h"
#include "Characters/StateMachine/CountrySelectionPawnState.h"

ACountrySelectionPawn::ACountrySelectionPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	
	MovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Movement component"));
}

void ACountrySelectionPawn::BeginPlay()
{
	Super::BeginPlay();

	MapActor = Cast<AMapActor>(GetWorld()->SpawnActor(MapActorClass));

	SetPawnState(FCountrySelectionPawnState::GetInstance());

	MovementComponent->Init(MapActor);
}

void ACountrySelectionPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MovementComponent->Move(DeltaSeconds);
}

void ACountrySelectionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Forward"), MovementComponent, &UPlayerMovementComponent::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Right"), MovementComponent, &UPlayerMovementComponent::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Scroll"), MovementComponent, &UPlayerMovementComponent::Scroll);
	PlayerInputComponent->BindAction(TEXT("LeftClick"), IE_Pressed, this, &ACountrySelectionPawn::LeftClick);
	PlayerInputComponent->BindAction(TEXT("RightClick"), IE_Pressed, this, &ACountrySelectionPawn::RightClick);
}

void ACountrySelectionPawn::SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState)
{
	PawnState = ProvidedPawnState;
}

TSharedPtr<FPawnState> ACountrySelectionPawn::GetPawnState() const
{
	return PawnState;
}

void ACountrySelectionPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ACountrySelectionPawn::LeftClick()
{
	SetPawnState(PawnState->LeftClick(this));
}

void ACountrySelectionPawn::RightClick()
{
	SetPawnState(PawnState->RightClick(this));
}
