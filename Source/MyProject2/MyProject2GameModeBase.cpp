// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProject2GameModeBase.h"

#include "Events/ConditionCheckers/Headers/ExactDateConditionChecker.h"
#include "Events/ConditionCheckers/Headers/StabilityConditionChecker.h"
#include "Characters/HumanPlayerPawn.h"
#include "Characters/MyPlayerController.h"
#include "Events/EventManager.h"
#include "Events/OutcomeAppliers/Headers/StabilityOutcomeApplier.h"

AMyProject2GameModeBase::AMyProject2GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultPawnClass = AHumanPlayerPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameState::StaticClass();

	const ConstructorHelpers::FObjectFinder<UDataTable> EventsDescription(TEXT("/Game/Sources/events_description"));

	if (EventsDescription.Succeeded())
	{
		EventsDataTable = EventsDescription.Object;
	}
}

void AMyProject2GameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!AreEventConditionCheckersInitialized)
	{
		InitializeEventModules();
		AreEventConditionCheckersInitialized = true;
	}
	
	EventManager->CheckEvents();
	EventManager->Tick();

	const FInGameTime* GameTime = static_cast<AMyGameState*>(GameState)->GetInGameTime();

	if (!GameTime->IsGamePaused())
	{
		if (TimeControllerWidget)
		{
			const FString Time = GameTime->GetTime()->ToString(TEXT("%Y-%m-%d %H"));
			TimeControllerWidget->SetTime(Time);
		}
	}
}

void AMyProject2GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (TimeControllerClass)
	{
		TimeControllerWidget = CreateWidget<UTimeController>(GetWorld(), TimeControllerClass);
		if (TimeControllerWidget)
		{
			TimeControllerWidget->BeginPlay();
			TimeControllerWidget->AddToViewport();
		}
	}

	if (EventsDataTable)
	{
		EventManager = new FEventManager(EventsDataTable, EventWidgetClass, GetWorld());
	}
}

void AMyProject2GameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EventManager)
	{
		delete EventManager;
	}

	if (TimeControllerWidget)
	{
		TimeControllerClass->RemoveFromRoot();
	}
	
	Super::EndPlay(EndPlayReason);
}

void AMyProject2GameModeBase::InitializeEventModules() const
{
	EventManager->RegisterConditionChecker("ExactDate", new FExactDateConditionChecker(GetGameState<AMyGameState>()->GetInGameTime()));
	EventManager->RegisterOutcomeApplier("Stability", new FStabilityOutcomeApplier(GetGameState<AMyGameState>()));
}