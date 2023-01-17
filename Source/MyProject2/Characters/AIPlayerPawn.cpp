// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPlayerPawn.h"

// Sets default values
AAIPlayerPawn::AAIPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAIPlayerPawn::SetRuledCountryTag(const FString& NewRuledCountryTag)
{
	RuledCountryTag = NewRuledCountryTag;
}

// Called when the game starts or when spawned
void AAIPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

