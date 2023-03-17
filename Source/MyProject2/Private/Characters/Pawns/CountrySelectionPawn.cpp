#include "Characters/Pawns/CountrySelectionPawn.h"

#include "MyGameInstance.h"

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

	MapActor = Cast<AMapActor>(GetWorld()->SpawnActor(MapActorClass));;

	MovementComponent->Init(MapActor);
	
	if (CountrySelectionWidgetClass)
	{
		CountrySelectionWidget = CreateWidget<UScenarioSelectionWidget>(GetController<APlayerController>(), CountrySelectionWidgetClass);
		if (CountrySelectionWidget)
		{
			CountrySelectionWidget->AddToPlayerScreen();
		}
	}
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
}

void ACountrySelectionPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CountrySelectionWidget)
	{
		CountrySelectionWidget->RemoveFromParent();
	}
	Super::EndPlay(EndPlayReason);
}
