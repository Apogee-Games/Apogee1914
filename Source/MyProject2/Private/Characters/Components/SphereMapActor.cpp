// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/SphereMapActor.h"


// Sets default values
ASphereMapActor::ASphereMapActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASphereMapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASphereMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

