// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProject2GameModeBase.h"

#include "Players/MyPawn.h"
#include "Players/MyPlayerController.h"

AMyProject2GameModeBase::AMyProject2GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameState::StaticClass();
}

void AMyProject2GameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!static_cast<AMyGameState*>(GameState)->IsGamePaused())
	{
		if (TimeControllerWidget)
		{
			const FString Time = static_cast<AMyGameState*>(GameState)->GetTime()->ToString(TEXT("%Y-%m-%d %H"));
			TimeControllerWidget->SetTime(Time);
		}
	}
}

void AMyProject2GameModeBase::BeginPlay()
{
	if (TimeControllerClass)
	{
		TimeControllerWidget = CreateWidget<UTimeController>(GetWorld(), TimeControllerClass);
		if (TimeControllerWidget)
		{
			TimeControllerWidget->BeginPlay();
			TimeControllerWidget->AddToViewport();
		}
	}
	Super::BeginPlay();
}

void AMyProject2GameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (TimeControllerWidget)
	{
		TimeControllerClass->RemoveFromRoot();
	}
	Super::EndPlay(EndPlayReason);
}
