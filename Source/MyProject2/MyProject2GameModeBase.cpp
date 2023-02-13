// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProject2GameModeBase.h"

#include "MyGameInstance.h"
#include "Characters/HumanPlayerPawn.h"
#include "Characters/MyPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Characters/AIPlayerPawn.h"
#include "Events/EventInstancesController.h"
#include "Maps/CountriesMap.h"
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
	GetWorld()->GetSubsystem<UEventInstancesController>()->Tick(DeltaSeconds);
	GetWorld()->GetSubsystem<UInGameTime>()->Tick(DeltaSeconds);
}

void AMyProject2GameModeBase::BeginPlay()
{
	// Add Unit Descriptions -> Add Widget For Unit Creation -> Tie Widget and Unit Creation
	
	// Beginning of Units Renderer/Factory Test Logic
	
	FUnitDescription* Description = new FUnitDescription();
	Description->CanTransport = true;
	Description->CanAccessProvincesTypes.Add("Land");

	UUnitsRenderer* Renderer = GetWorld()->GetSubsystem<UUnitsRenderer>();
	
	UUnit* Unit1 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(Description, FColor(202, 160, 1), "GER",Renderer);
	UUnit* Unit2 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(Description, FColor(246, 39, 1), "GER",Renderer);
	UUnit* Unit3 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(Description, FColor(239, 236, 1), "GER",Renderer);
	UUnit* Unit4 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(Description, FColor(231, 116, 1), "NET",Renderer);

	GetWorld()->GetSubsystem<UUnitsMover>()->SetGraph(new FGraph({}));

	GetWorld()->GetSubsystem<UUnitsMover>()->MoveUnit(Unit3, FColor(246, 39, 1));
	GetWorld()->GetSubsystem<UUnitsMover>()->MoveUnit(Unit4, FColor(246, 39, 1));

	// End of Test Logic

	Super::BeginPlay();
	
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
}

void AMyProject2GameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
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
