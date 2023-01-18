// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProject2GameModeBase.h"

#include "MyGameInstance.h"
#include "Events/ConditionCheckers/Headers/ExactDateConditionChecker.h"
#include "Events/ConditionCheckers/Headers/StabilityConditionChecker.h"
#include "Characters/HumanPlayerPawn.h"
#include "Characters/MyPlayerController.h"
#include "Events/EventManager.h"
#include "Events/OutcomeAppliers/Headers/StabilityOutcomeApplier.h"
#include "GameFramework/PlayerState.h"
#include "Characters/AIPlayerPawn.h"

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


	// Temporary initialization of Ruled tag will be removed when lobby will be added
	const int LocalPlayerControllersNumber = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int PlayerIndex = 0; PlayerIndex < LocalPlayerControllersNumber; ++PlayerIndex) {
		const AMyPlayerController* Controller = static_cast<AMyPlayerController*>(UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex));

		const AHumanPlayerPawn* Pawn = Controller->GetPawn<AHumanPlayerPawn>();
		const int32 PlayerId = Pawn->GetPlayerState()->GetPlayerId();

		UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();

		GameInstance->SetRuledCountry(PlayerId, "GER");
	}
	
	InitializeRuledCountry();

	CreateAIPawns();
	
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

void AMyProject2GameModeBase::InitializeRuledCountry() const
{
	InitializeRuledCountryForLocalPlayers();
	// TODO:: Add Ruled Country initialization for net Players
}

void AMyProject2GameModeBase::InitializeRuledCountryForLocalPlayers() const
{
	const int LocalPlayerControllersNumber = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int PlayerIndex = 0; PlayerIndex < LocalPlayerControllersNumber; ++PlayerIndex) {
		const AMyPlayerController* Controller = static_cast<AMyPlayerController*>(UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex));

		AHumanPlayerPawn* Pawn = Controller->GetPawn<AHumanPlayerPawn>();
		const int32 PlayerId = Pawn->GetPlayerState()->GetPlayerId();

		const UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();
		const FString RuledCountryTag = GameInstance->GetRuledCountry(PlayerId);
		
		Pawn->SetRuledCountryTag(RuledCountryTag);
	}
}

void AMyProject2GameModeBase::CreateAIPawns()
{
	for (const auto& CountryTag: GetGameState<AMyGameState>()->GetCountriesTagsList())
	{
		if (GetGameInstance<UMyGameInstance>()->IsCountryRuledByPlayer(CountryTag)) continue;
		AAIPlayerPawn* Pawn = GetWorld()->SpawnActor<AAIPlayerPawn>(AAIPlayerPawn::StaticClass());
		Pawn->SetRuledCountryTag(CountryTag);
		AIPawns.Add(CountryTag, Pawn);
	}
}
