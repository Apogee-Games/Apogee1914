// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/MapActor.h"
#include "Components/UnitsSelectionComponent.h"
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
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	UUnitsSelectionComponent* UnitSelectionComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapActor> MapActorClass;
	
	UPROPERTY()
	AMapActor* MapActor;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	AHumanPlayerPawn();

	void SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState);
	
	// Sets tag of country controlled by this Pawn
	void SetRuledCountryTag(const FName& NewRuledCountryTag);

	TSharedPtr<FPawnState> GetPawnState() const;

	void SelectUnitDescription(const FUnitDescription* UnitDescription);

	void SelectBuildingDescription(const FBuildingDescription* BuildingDescription);

	void SetCommandable(ICommandable* Commandable);

	ICommandable* GetSelectedCommandable() const;
		
	const FUnitDescription* GetSelectedUnitDescription() const;

	const FBuildingDescription* GetSelectedBuildingDescription() const;

	const FName& GetRuledCountryTag() const;

	UCountry* GetRuledCountry() const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool IsShiftPressed() const;
	
	UPROPERTY(EditAnywhere)
	FVector SpeedVector;
private:
	TSharedPtr<FPawnState> PawnState = nullptr;
	
	UPROPERTY()
	UCountry* RuledCountry;

	bool bIsShiftPressed = false;

	const FUnitDescription* SelectedUnitDescription;
	
	const FBuildingDescription* SelectedBuildingDescription;

	ICommandable* SelectedCommandable;
	
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
};
