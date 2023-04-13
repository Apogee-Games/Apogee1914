// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Characters/Components/MapActor.h"
#include "Characters/Components/PlayerMovementComponent.h"
#include "Characters/Components/UnitsSelectionComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Military/Descriptions/UnitDescription.h"
#include "Military/Instances/Units/Unit.h"
#include "Characters/StateMachine/PawnState.h"
#include "Widgets/Economics/Buildings/Production/FactoryProductionWidget.h"
#include "Widgets/Music/MusicControllerWidget.h"
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

	UPROPERTY()
	UPlayerMovementComponent* MovementComponent;

	UPROPERTY()
	UAudioComponent* AudioComponent;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	AHumanPlayerPawn();

	void SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState);
	
	void SetRuledCountry(UCountry* Country);

	TSharedPtr<FPawnState> GetPawnState() const;

	void SelectUnitDescription(UUnitDescription* UnitDescription);

	void SelectBuildingDescription(UBuildingDescription* BuildingDescription);

	void SetCommandable(ICommandable* Commandable);

	ICommandable* GetSelectedCommandable() const;
		
	UUnitDescription* GetSelectedUnitDescription() const;

	UBuildingDescription* GetSelectedBuildingDescription() const;

	const FName& GetRuledCountryTag() const;

	UCountry* GetRuledCountry() const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool IsShiftPressed() const;

	void Pause();

	void UnPause();

	void SwitchUnitCreationState();

	void SwitchStorageBrowsingState();

	void SwitchSupplyBrowsingState();

	void SwitchBuildingCreationState();

	void SwitchCountryManagementState();

	void SwitchLawsBrowsingState();

	void SwitchProductionBrowsingState();

	void Play(USoundBase* Song);

	void SetIsAudioPaused(bool IsAudioPaused);

	void SetProductionSelectionFactory(UFactoryBuilding* Factory);

	UFactoryBuilding* GetSelectedFactory() const;

	AMapActor* GetMapActor();
private:
	TSharedPtr<FPawnState> PawnState = nullptr;
	
	bool IsPaused = false;
	
	UPROPERTY()
	UCountry* RuledCountry;

	bool bIsShiftPressed = false;

	UPROPERTY()
	UUnitDescription* SelectedUnitDescription;

	UPROPERTY()
	UBuildingDescription* SelectedBuildingDescription;

	ICommandable* SelectedCommandable;

	UPROPERTY()
	UFactoryBuilding* SelectedFactory;
	
	void LeftClick();

	void RightClick();

	void ShiftPressed();
	
	void ShiftReleased();

	void SwitchPause();

	void InitMapActor();
};
