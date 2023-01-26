// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayerPawn.h"
#include "EngineUtils.h"
#include "MyPlayerController.h"
#include "MyProject2/MousePosition.h"
#include "MyProject2/Managers/ProvinceManager.h"
#include "MyProject2/Maps/SelectionMap.h"

// Sets default values
AHumanPlayerPawn::AHumanPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

void AHumanPlayerPawn::SetRuledCountryTag(const FString& NewRuledCountryTag)
{
	RuledCountryTag = NewRuledCountryTag;
}

void AHumanPlayerPawn::MoveUp(float Value)
{
	MovementDirection.Y = FMath::Clamp(Value, -1.f, 1.f);
}

void AHumanPlayerPawn::MoveRight(float Value)
{
	MovementDirection.Z = FMath::Clamp(Value, -1.f, 1.f);
}

void AHumanPlayerPawn::LeftClick()
{
	USelectionMap* SelectionMap = GetGameInstance()->GetSubsystem<USelectionMap>();

	const FVector Point = GetNormalizedPositionOnPlane();

	const FColor Color = SelectionMap->GetProvinceColor(FVector2D(Point.Y, Point.Z));

	SelectionMap->SelectProvince(Color);

	const auto ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();

	const UProvince* Province = ProvinceManager->GetProvince(Color);

	if (Province)
	{
		ProvinceDataWidget->SetProvinceName(Province->GetProvinceName());
		ProvinceDataWidget->SetPopulationNumber(FString::FromInt(Province->GetPopulation()->GetPopulation()));
		ProvinceDataWidget->SetResources(Province->GetResources());

		const FState* State = ProvinceManager->GetState(Province->GetStateId());

		if (State)
		{
			ProvinceDataWidget->SetStateName(State->StateName);
		}
	}
}

FVector AHumanPlayerPawn::GetNormalizedPositionOnPlane() const
{
	const FMousePosition MousePosition(GetWorld()->GetFirstPlayerController());
	FVector Point = FMath::RayPlaneIntersection(MousePosition.GetMouseLocation(),
	                                            MousePosition.GetMouseDirection(),
	                                            Plane);

	Point /= PlaneSize;

	Point.Z = 1 - Point.Z;

	return Point;
}

AMyGameState* AHumanPlayerPawn::GetGameState() const
{
	return static_cast<AMyGameState*>(GetWorld()->GetGameState());
}

// Called when the game starts or when spawned
void AHumanPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled() && ProvinceDataWidgetClass)
	{
		AMyPlayerController* PlayerController = GetController<AMyPlayerController>();
		ProvinceDataWidget = CreateWidget<UProvinceData>(PlayerController, ProvinceDataWidgetClass);
		if (ProvinceDataWidget)
		{
			ProvinceDataWidget->AddToPlayerScreen();
		}
	}
}

void AHumanPlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ProvinceDataWidget)
	{
		ProvinceDataWidget->RemoveFromParent();
	}

	Super::EndPlay(EndPlayReason);
}


// Called every frame
void AHumanPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void AHumanPlayerPawn::Move(float DeltaTime)
{
	if ((MovementDirection == FVector(0, 0, 0) && RotationDirection == FRotator(0, 0, 0)) ||
		SpeedVector == FVector(0, 0, 0))
		return;

	const FVector MovementVector = MovementDirection * DeltaTime * SpeedVector;

	const FVector NewPosition = GetActorLocation() + MovementVector;

	if (IsInside(NewPosition))
	{
		SetActorLocation(NewPosition);
		Camera->AddRelativeRotation(FQuat(RotationDirection * RotationSpeed));
	}
}

void AHumanPlayerPawn::Scroll(float Value)
{
	MovementDirection.X = FMath::Clamp(Value, -1, 1);
	RotationDirection.Pitch = FMath::Clamp(Value, -1, 1);
}

bool AHumanPlayerPawn::IsInside(const FVector& Position) const
{
	return Position.X >= MinXPosition && Position.X <= MaxXPosition &&
		Position.Y >= MinYPosition && Position.Y <= MaxYPosition &&
		Position.Z >= MinZPosition && Position.Z <= MaxZPosition;
}

// Called to bind functionality to input
void AHumanPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AHumanPlayerPawn::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AHumanPlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Scroll"), this, &AHumanPlayerPawn::Scroll);
	PlayerInputComponent->BindAction(TEXT("Click"), IE_Pressed, this, &AHumanPlayerPawn::LeftClick);
}
