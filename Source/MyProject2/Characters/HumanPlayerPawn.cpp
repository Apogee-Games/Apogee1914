// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayerPawn.h"
#include "EngineUtils.h"
#include "MyPlayerController.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Maps/Selection/SelectionMap.h"
#include "MyProject2/Military/Managers/UnitsMover.h"
#include "StateMachine/MilitaryControlPawnState.h"
#include "StateMachine/MapBrowsingPawnState.h"
#include "StateMachine/StorageBrowsingPawnState.h"
#include "StateMachine/SupplyBrowsingPawnState.h"
#include "StateMachine/UnitCreationPawnState.h"

// Sets default values
AHumanPlayerPawn::AHumanPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

}

void AHumanPlayerPawn::SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState)
{
	if (PawnState == ProvidedPawnState) return;
	PawnState = ProvidedPawnState;
	UpdateWidgetsVisibility();
}

void AHumanPlayerPawn::SetRuledCountryTag(const FName& NewRuledCountryTag)
{
	RuledCountryTag = NewRuledCountryTag;
}

void AHumanPlayerPawn::SelectUnits(const TArray<FUnit*>& Units)
{
	SetPawnState(FMilitaryControlPawnState::GetInstance());
	
	if (!IsShiftPressed)
	{
		SelectedUnits.Empty();
	}
	for (const auto& Unit: Units)
	{
		SelectedUnits.Add(Unit);
	}
}

void AHumanPlayerPawn::SelectUnit(FUnit* Unit)
{
	SetPawnState(FMilitaryControlPawnState::GetInstance());

	if (!IsShiftPressed)
	{
		SelectedUnits.Empty();
	}
	SelectedUnits.Add(Unit);
	// TODO: Add check for controlled country
}

void AHumanPlayerPawn::ClearSelectedUnits()
{
	SelectedUnits.Empty();
}

const TArray<FUnit*>& AHumanPlayerPawn::GetSelectedUnits() const
{
	return SelectedUnits;
}

UProvinceDataWidget* AHumanPlayerPawn::GetProvinceDataWidget() const
{
	return ProvinceDataWidget;
}

void AHumanPlayerPawn::SelectUnitDescription(const FUnitDescription* UnitDescription)
{
	SetPawnState(FUnitCreationPawnState::GetInstance());
	SelectedUnitDescription = UnitDescription;
}

const FUnitDescription* AHumanPlayerPawn::GetSelectedUnitDescription() const
{
	return SelectedUnitDescription;
}

const FName& AHumanPlayerPawn::GetRuledCountryTag() const
{
	return RuledCountryTag;
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
	SetPawnState(PawnState->LeftClick(this));
}

void AHumanPlayerPawn::RightClick()
{
	SetPawnState(PawnState->RightClick(this));
}

void AHumanPlayerPawn::ShiftPressed()
{
	IsShiftPressed = true;
}

// Called when the game starts or when spawned
void AHumanPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	InitProvinceDataWidget();
	InitUnitTypesListWidget();
	InitStorageGoodsListWidget();
	InitUnitsSupplyListWidget();

	SetPawnState(FMapBrowsingPawnState::GetInstance());
}

void AHumanPlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ProvinceDataWidget)
	{
		ProvinceDataWidget->RemoveFromParent();
	}

	if (UnitTypesListWidget)
	{
		UnitTypesListWidget->RemoveFromParent();
	}

	if (StorageGoodsListWidget)
	{
		StorageGoodsListWidget->RemoveFromParent();
	}

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AHumanPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void AHumanPlayerPawn::ShiftReleased()
{
	IsShiftPressed = false;
}

void AHumanPlayerPawn::SetUnitCreationState()
{
	if (PawnState == FUnitCreationPawnState::GetInstance())
	{
		 SetPawnState(FMapBrowsingPawnState::GetInstance());
	} else {
		SetPawnState(FUnitCreationPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SetStorageBrowsingState()
{
	if (PawnState == FStorageBrowsingPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	} else {
		SetPawnState(FStorageBrowsingPawnState::GetInstance());
	}
}

void AHumanPlayerPawn::SetSupplyBrowsingState()
{
	if (PawnState == FSupplyBrowsingPawnState::GetInstance())
	{
		SetPawnState(FMapBrowsingPawnState::GetInstance());
	} else {
		SetPawnState(FSupplyBrowsingPawnState::GetInstance());
	}
}


void AHumanPlayerPawn::UpdateWidgetsVisibility()
{
	for (const auto& Widget: Widgets)
	{
		if (PawnState->MustWidgetBeVisible(Widget))
		{
			Widget->AddToPlayerScreen();
			continue;
		}
		
		if (PawnState->CanWidgetBeVisible(Widget))
		{
			continue;
		}
		
		Widget->RemoveFromViewport();
	}
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

void AHumanPlayerPawn::InitProvinceDataWidget()
{
	const TSubclassOf<UProvinceDataWidget> ProvinceDataWidgetClass = GetWorld()->GetGameState<AMyGameState>()->ProvinceDataWidgetClass;
	
	if (IsLocallyControlled() && ProvinceDataWidgetClass)
	{
		AMyPlayerController* PlayerController = GetController<AMyPlayerController>();
		ProvinceDataWidget = CreateWidget<UProvinceDataWidget>(PlayerController, ProvinceDataWidgetClass);
		if (ProvinceDataWidget)
		{
			Widgets.Add(ProvinceDataWidget);
		}
	}
}

void AHumanPlayerPawn::InitUnitTypesListWidget()
{
	const TSubclassOf<UUnitTypesListWidget> UnitTypesListWidgetClass = GetWorld()->GetGameState<AMyGameState>()->UnitTypesListWidgetClass;
	
	if (IsLocallyControlled() && UnitTypesListWidgetClass)
	{
		AMyPlayerController* PlayerController = GetController<AMyPlayerController>();
		
		UnitTypesListWidget = CreateWidget<UUnitTypesListWidget>(PlayerController, UnitTypesListWidgetClass);
		
		if (UnitTypesListWidget)
		{
			UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/units_description"));

			for (const auto& [UnitName, UnitDescription]: DataTable->GetRowMap())
			{
				UnitTypesListWidget->AddUnitType(reinterpret_cast<FUnitDescription*>(UnitDescription));
			}
			Widgets.Add(UnitTypesListWidget);
		}
	}
}

void AHumanPlayerPawn::InitStorageGoodsListWidget()
{
	const TSubclassOf<UStorageGoodsListWidget> StorageGoodsListWidgetClass = GetWorld()->GetGameState<AMyGameState>()->StorageGoodsListWidgetClass;
	
	if (IsLocallyControlled() && StorageGoodsListWidgetClass)
	{
		AMyPlayerController* PlayerController = GetController<AMyPlayerController>();
		StorageGoodsListWidget = CreateWidget<UStorageGoodsListWidget>(PlayerController, StorageGoodsListWidgetClass);
		if (StorageGoodsListWidget)
		{
			const UCountry* Country = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(RuledCountryTag);

			for (const auto& Storage: Country->GetStorages())
			{
				Storage->AddStorageObserver(StorageGoodsListWidget);
			}

			Widgets.Add(StorageGoodsListWidget);
		}
	}
}

void AHumanPlayerPawn::InitUnitsSupplyListWidget()
{
	const TSubclassOf<UUnitsSupplyListWidget> UnitsSupplyListWidgetClass = GetWorld()->GetGameState<AMyGameState>()->UnitsSupplyListWidgetClass;
	
	if (IsLocallyControlled() && UnitsSupplyListWidgetClass)
	{
		AMyPlayerController* PlayerController = GetController<AMyPlayerController>();
		UnitsSupplyListWidget = CreateWidget<UUnitsSupplyListWidget>(PlayerController, UnitsSupplyListWidgetClass);
		if (UnitsSupplyListWidget)
		{
			UnitsSupplyListWidget->Init();
			Widgets.Add(UnitsSupplyListWidget);
		}
	}
}

// Called to bind functionality to input
void AHumanPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AHumanPlayerPawn::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AHumanPlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Scroll"), this, &AHumanPlayerPawn::Scroll);
	PlayerInputComponent->BindAction(TEXT("LeftClick"), IE_Pressed, this, &AHumanPlayerPawn::LeftClick);
	PlayerInputComponent->BindAction(TEXT("RightClick"), IE_Pressed, this, &AHumanPlayerPawn::RightClick);
	PlayerInputComponent->BindAction(TEXT("Shift"), IE_Pressed, this, &AHumanPlayerPawn::ShiftPressed);
	PlayerInputComponent->BindAction(TEXT("Shift"), IE_Released, this, &AHumanPlayerPawn::ShiftReleased);
	PlayerInputComponent->BindAction(TEXT("UKey"), IE_Pressed, this, &AHumanPlayerPawn::SetUnitCreationState);
	PlayerInputComponent->BindAction(TEXT("SKey"), IE_Pressed, this, &AHumanPlayerPawn::SetStorageBrowsingState);
	PlayerInputComponent->BindAction(TEXT("PKey"), IE_Pressed, this, &AHumanPlayerPawn::SetSupplyBrowsingState);
}
