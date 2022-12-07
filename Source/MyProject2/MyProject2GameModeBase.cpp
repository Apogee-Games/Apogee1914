// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProject2GameModeBase.h"

#include "Players/MyPawn.h"
#include "Players/MyPlayerController.h"

AMyProject2GameModeBase::AMyProject2GameModeBase()
{
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AMyProject2GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Widget = CreateWidget<UMyUserWidget>(GetWorld(), WidgetClass);
	//Widget->AddToViewport();
}
