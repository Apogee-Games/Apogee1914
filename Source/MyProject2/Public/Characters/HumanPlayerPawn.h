// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/Units/Unit.h"
#include "StateMachine/PawnState.h"
#include "HumanPlayerPawn.generated.h"

UCLASS()
class MYPROJECT2_API AHumanPlayerPawn : public APawn
{
	GENERATED_BODY()
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	AHumanPlayerPawn();

	void SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState);
	
	// Sets tag of country controlled by this Pawn
	void SetRuledCountryTag(const FName& NewRuledCountryTag);

	void SelectUnits(const TArray<UUnit*>& Units);

	void SelectUnit(UUnit* Unit);

	void ClearSelectedUnits();

	const TArray<UUnit*>& GetSelectedUnits() const;

	TSharedPtr<FPawnState> GetPawnState() const;

	void SelectUnitDescription(const FUnitDescription* UnitDescription);

	void SelectBuildingDescription(const FBuildingDescription* BuildingDescription);

	const FUnitDescription* GetSelectedUnitDescription() const;

	const FBuildingDescription* GetSelectedBuildingDescription() const;

	const FName& GetRuledCountryTag() const;

	UCountry* GetRuledCountry() const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	FVector SpeedVector;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditAnywhere)
	FRotator PlaneRotator = FRotator(90, 0, 90);

	UPROPERTY(EditAnywhere)
	double MinXPosition = 0;

	UPROPERTY(EditAnywhere)
	double MaxXPosition = 200;

	UPROPERTY(EditAnywhere)
	double MinYPosition = 0;

	UPROPERTY(EditAnywhere)
	double MaxYPosition = 120;

	UPROPERTY(EditAnywhere)
	double MinZPosition = 0;

	UPROPERTY(EditAnywhere)
	double MaxZPosition = 120;

private:
	TSharedPtr<FPawnState> PawnState = nullptr;
	
	UPROPERTY()
	UCountry* RuledCountry;

	bool IsShiftPressed = false;

	UPROPERTY()
	TArray<UUnit*> SelectedUnits;

	const FUnitDescription* SelectedUnitDescription;
	
	const FBuildingDescription* SelectedBuildingDescription;
	
	FVector MovementDirection = FVector(0, 0, 0);

	FRotator RotationDirection = FRotator(0, 0, 0);

	void MoveUp(float Value);

	void MoveRight(float Value);

	void LeftClick();

	void RightClick();

	void ShiftPressed();
	
	void ShiftReleased();

	void SetUnitCreationState();

	void SetStorageBrowsingState();

	void SetSupplyBrowsingState();

	void SetBuildingCreationState();
	
	void Move(float DeltaTime);

	void Scroll(float Value);

	bool IsInside(const FVector& Position) const;

	void SelectedUnitsWereUpdated() const;
};
