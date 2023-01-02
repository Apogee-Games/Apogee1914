// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "EngineUtils.h"
#include "MyPlayerController.h"
#include "MyProject2/MousePosition.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

void AMyPawn::MoveUp(float Value)
{
	MovementDirection.Y = FMath::Clamp(Value, -1.f, 1.f);
}

void AMyPawn::MoveRight(float Value)
{
	MovementDirection.Z = FMath::Clamp(Value, -1.f, 1.f);
}

void AMyPawn::LeftClick()
{
	std::cout << "Clicked" << std::endl;

	const FVector Point = GetNormalizedPositionOnPlane();

	const FColor Color = MapManager.GetProvinceColor(FVector2D(Point.Y, Point.Z));

	MapManager.Select(Color);

	const FProvince Province = ((AMyGameState*)GetWorld()->GetGameState())->GetProvince(Color);

	ProvinceDataWidget->SetProvinceName(Province.GetName());
	ProvinceDataWidget->SetPopulationNumber(FString::FromInt(Province.GetPopulation()));
}

FVector AMyPawn::GetNormalizedPositionOnPlane() const
{
	FMousePosition MousePosition(GetWorld()->GetFirstPlayerController());
	FVector Point = FMath::RayPlaneIntersection(MousePosition.GetMouseLocation(),
	                                            MousePosition.GetMouseDirection(),
	                                            Plane);

	Point /= PlaneSize;

	Point.Z = 1 - Point.Z;

	return Point;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	MapManager.SetGameState((AMyGameState*)GetWorld()->GetGameState());

	MapManager.UpdateCountriesMapColors();

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

void AMyPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ProvinceDataWidget)
	{
		ProvinceDataWidget->RemoveFromParent();
	}
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void AMyPawn::Move(float DeltaTime)
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

void AMyPawn::Scroll(float Value)
{
	MovementDirection.X = FMath::Clamp(Value, -1, 1);
	RotationDirection.Pitch = FMath::Clamp(Value, -1, 1);
}

bool AMyPawn::IsInside(const FVector& Position) const
{
	return Position.X >= MinXPosition && Position.X <= MaxXPosition &&
		Position.Y >= MinYPosition && Position.Y <= MaxYPosition &&
		Position.Z >= MinZPosition && Position.Z <= MaxZPosition;
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AMyPawn::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Scroll"), this, &AMyPawn::Scroll);
	PlayerInputComponent->BindAction(TEXT("Click"), IE_Pressed, this, &AMyPawn::LeftClick);
}
