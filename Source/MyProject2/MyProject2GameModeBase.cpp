// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProject2GameModeBase.h"

#include "MyGameInstance.h"
#include "Events/ConditionCheckers/Headers/ExactDateConditionChecker.h"
#include "Characters/HumanPlayerPawn.h"
#include "Characters/MyPlayerController.h"
#include "Events/OutcomeAppliers/Headers/StabilityOutcomeApplier.h"
#include "GameFramework/PlayerState.h"
#include "Characters/AIPlayerPawn.h"
#include "Events/EventInstancesController.h"
#include "Events/ConditionCheckers/Headers/DatePassedConditionChecker.h"
#include "Events/ConditionCheckers/Headers/EventContitionsChecker.h"
#include "Events/OutcomeAppliers/Headers/EventsOutcomesApplier.h"
#include "Maps/CountriesMap.h"
#include "Maps/FlagsMap.h"
#include "Maps/ObjectMap.h"
#include "Maps/OutlineMap.h"
#include "Military/Instances/Unit.h"
#include "Military/Managers/UnitsFactory.h"
#include "Military/Managers/UnitsMover.h"

AMyProject2GameModeBase::AMyProject2GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultPawnClass = AHumanPlayerPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameState::StaticClass();
}

void AMyProject2GameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!AreEventConditionCheckersInitialized)
	{
		InitializeEventModules();
		AreEventConditionCheckersInitialized = true;
	}
	
	const FInGameTime* GameTime = static_cast<AMyGameState*>(GameState)->GetInGameTime();

	if (!GameTime->IsGamePaused())
	{
		if (TimeControllerWidget)
		{
			const FString Time = GameTime->GetTime()->ToString(TEXT("%Y-%m-%d %H"));
			TimeControllerWidget->SetTime(Time);
		}
	}

	GetWorld()->GetSubsystem<UEventInstancesController>()->Tick(*GameTime->GetTime());

	GetWorld()->GetSubsystem<UUnitsMover>()->Tick();
}

void AMyProject2GameModeBase::BeginPlay()
{
	GetWorld()->GetSubsystem<UUnitsRenderer>()->SetUnitInformationWidgetClass(UnitInformationListWidgetClass);

	GetWorld()->GetSubsystem<UUnitsRenderer>()->BeginPlay();
	
	Super::BeginPlay();

	// Beginning of Units Renderer/Factory Test Logic
	
	FUnitDescription* Description = new FUnitDescription();
	Description->CanTransport = true;
	Description->CanAccessProvincesTypes.Add("Land");

	UUnitsRenderer* Renderer = GetWorld()->GetSubsystem<UUnitsRenderer>();
	
	UUnit* Unit1 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(Description, FColor(202, 160, 1, 0), "GER",Renderer);
	UUnit* Unit2 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(Description, FColor(246, 39, 1, 0), "GER",Renderer);
	UUnit* Unit3 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(Description, FColor(239, 236, 1, 0), "GER",Renderer);
	UUnit* Unit4 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(Description, FColor(231, 116, 1, 0), "NET",Renderer);

	GetWorld()->GetSubsystem<UUnitsMover>()->SetGraph(new FGraph({}));

	GetWorld()->GetSubsystem<UUnitsMover>()->MoveUnit(Unit3, FColor(246, 39, 1, 0));
	GetWorld()->GetSubsystem<UUnitsMover>()->MoveUnit(Unit4, FColor(246, 39, 1, 0));

	// End of Test Logic

	GetWorld()->GetSubsystem<UEventInstancesController>()->SetEventWidgetClass(EventWidgetClass);
	
	GetWorld()->GetSubsystem<UCountriesMap>()->UpdateCountriesMapColors();

	//GetWorld()->GetSubsystem<UFlagsMap>()->UpdateFlagsMapColors();

	//GetWorld()->GetSubsystem<UOutlineMap>()->CreateOutline();
	
	// Temporary initialization of Ruled tag will be removed when lobby will be added
	const int LocalPlayerControllersNumber = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int PlayerIndex = 0; PlayerIndex < LocalPlayerControllersNumber; ++PlayerIndex)
	{
		const AMyPlayerController* Controller = static_cast<AMyPlayerController*>(UGameplayStatics::GetPlayerController(
			GetWorld(), PlayerIndex));

		const AHumanPlayerPawn* Pawn = Controller->GetPawn<AHumanPlayerPawn>();
		const int32 PlayerId = Pawn->GetPlayerState()->GetPlayerId();

		UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();

		GameInstance->SetRuledCountry(PlayerId, "GER");
	}
	
	InitializeRuledCountry();

	//CreateAIPawns();
	
	if (TimeControllerClass)
	{
		TimeControllerWidget = CreateWidget<UTimeController>(GetWorld(), TimeControllerClass);
		if (TimeControllerWidget)
		{
			TimeControllerWidget->BeginPlay();
			TimeControllerWidget->AddToViewport();
		}
	}

}

void AMyProject2GameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	if (TimeControllerWidget)
	{
		TimeControllerClass->RemoveFromRoot();
	}
	
	Super::EndPlay(EndPlayReason);
}

void AMyProject2GameModeBase::InitializeEventModules() const
{
	GetWorld()->GetSubsystem<UEventConditionsChecker>()->RegisterConditionChecker("ExactDate", new FExactDateConditionChecker(GetGameState<AMyGameState>()->GetInGameTime()));
	GetWorld()->GetSubsystem<UEventConditionsChecker>()->RegisterConditionChecker("DatePassed", new FDatePassedConditionChecker(GetGameState<AMyGameState>()->GetInGameTime()));
	GetWorld()->GetSubsystem<UEventsOutcomesApplier>()->RegisterOutcomeApplier("Stability", new FStabilityOutcomeApplier(GetGameState<AMyGameState>()));
}

void AMyProject2GameModeBase::InitializeRuledCountry() const
{
	InitializeRuledCountryForLocalPlayers();
	// TODO:: Add Ruled Country initialization for net Players
}

void AMyProject2GameModeBase::InitializeRuledCountryForLocalPlayers() const
{
	const int LocalPlayerControllersNumber = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int PlayerIndex = 0; PlayerIndex < LocalPlayerControllersNumber; ++PlayerIndex)
	{
		const AMyPlayerController* Controller = static_cast<AMyPlayerController*>(UGameplayStatics::GetPlayerController(
			GetWorld(), PlayerIndex));

		AHumanPlayerPawn* Pawn = Controller->GetPawn<AHumanPlayerPawn>();
		const int32 PlayerId = Pawn->GetPlayerState()->GetPlayerId();

		const UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();
		const FString RuledCountryTag = GameInstance->GetRuledCountry(PlayerId);
		
		Pawn->SetRuledCountryTag(RuledCountryTag);
	}
}

void AMyProject2GameModeBase::CreateAIPawns()
{
	for (const auto& CountryTag : *GetWorld()->GetSubsystem<UCountriesManager>()->GetCountriesTagsList())
	{
		if (GetGameInstance<UMyGameInstance>()->IsCountryRuledByPlayer(CountryTag)) continue;
		AAIPlayerPawn* Pawn = GetWorld()->SpawnActor<AAIPlayerPawn>(AAIPlayerPawn::StaticClass());
		Pawn->SetRuledCountryTag(CountryTag);
		AIPawns.Add(CountryTag, Pawn);
	}
}
