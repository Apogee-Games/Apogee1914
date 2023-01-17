// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"


AMyPlayerController::AMyPlayerController() 
{
	bShowMouseCursor = true;
	
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}