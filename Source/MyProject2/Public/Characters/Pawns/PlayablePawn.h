// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/StateMachine/PawnState.h"
#include "Characters/Components/MapActor.h"
#include "Templates/SharedPointer.h"
#include "PlayablePawn.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPawnStateChanged, TSharedPtr<FPawnState>)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPauseChanged, bool)

UCLASS()
class MYPROJECT2_API APlayablePawn : public APawn
{
	GENERATED_BODY()

public:
	APlayablePawn();

	UPROPERTY(EditDefaultsOnly) class USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditDefaultsOnly) class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<AMapActor> MapActorClass;
	UPROPERTY(EditDefaultsOnly) AMapActor* MapActor;

	UPROPERTY(EditDefaultsOnly) class UPlayerMovementComponent* MovementComponent;

	FOnPawnStateChanged OnPawnStateChanged;
	FOnPauseChanged OnPauseChanged;

	virtual void BeginPlay() override;
	
	void SetPawnState(TSharedPtr<FPawnState> ProvidedPawnState);
	TSharedPtr<FPawnState> GetPawnState() const;

	template<class T>
	void SwitchState();

	void SwitchPause();
	void Pause();
	void UnPause();
	
	AMapActor* GetMapActor();

	bool ShouldAppend() const;
protected:
	bool bShouldAppend = false;

	TSharedPtr<FPawnState> PawnState = nullptr;

	void ShouldAppendYes();
	void ShouldAppendNo();
	
	void LeftClick();
	void RightClick();

	bool bIsPaused = false;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};


template <class T>
void APlayablePawn::SwitchState()
{
	if (PawnState == T::GetInstance())
	{
		SetPawnState(T::GetInstance());
	}
	else
	{
		SetPawnState(T::GetInstance());
	}
}