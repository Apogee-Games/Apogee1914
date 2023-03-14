// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIPlayerPawn.generated.h"

UCLASS()
class MYPROJECT2_API AAIPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPlayerPawn();
	
	// Sets tag of country controlled by this Pawn
	void SetRuledCountryTag(const FName& NewRuledCountryTag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	/* Tag of country that current pawn controls */
	FName RuledCountryTag;
	
};