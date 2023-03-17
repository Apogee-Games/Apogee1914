// Copyright Epic Games, Inc. All Rights Reserved.


#include "LevelsOverides/Game/GameLevelGameMode.h"

#include "InGameTime.h"
#include "MyGameInstance.h"
#include "Administration/Managers/CountriesManager.h"
#include "Characters/HumanPlayerPawn.h"
#include "GameFramework/PlayerState.h"
#include "Characters/AIPlayerPawn.h"
#include "Characters/HumanPlayerHUD.h"
#include "Events/EventInstancesController.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Military/Managers/UnitsMover.h"

AGameLevelGameMode::AGameLevelGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultPawnClass = AHumanPlayerPawn::StaticClass();
	GameStateClass = AGameLevelGameState::StaticClass();
	HUDClass = AHumanPlayerHUD::StaticClass();
}

void AGameLevelGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GetWorld()->GetSubsystem<UEventInstancesController>()->Tick(DeltaSeconds);
	GetWorld()->GetSubsystem<UInGameTime>()->Tick(DeltaSeconds);
}

void AGameLevelGameMode::BeginPlay()
{
	// Add Unit Descriptions -> Add Widget For Unit Creation -> Tie Widget and Unit Creation

	//GetWorld()->Exec(GetWorld(), TEXT("viewmode unlit"));
	
	GetWorld()->GetSubsystem<UUnitsMover>()->SetGraph(new FGraph({}));
	
	Super::BeginPlay();
	
	// Temporary initialization of Ruled tag will be removed when lobby will be added
	/*const int32 LocalPlayerControllersNumber = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int32 PlayerIndex = 0; PlayerIndex < LocalPlayerControllersNumber; ++PlayerIndex)
	{
		const APlayerController* Controller = static_cast<APlayerController*>(UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex));

		const AHumanPlayerPawn* Pawn = Controller->GetPawn<AHumanPlayerPawn>();
		const int32 PlayerId = Pawn->GetPlayerState()->GetPlayerId();

		UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();

		GameInstance->SetRuledCountry(PlayerId, "GER");
	}*/
	
	//CreateAIPawns();
}

void AGameLevelGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGameLevelGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	NewPlayer->SetInputMode(InputModeGameAndUI);
	NewPlayer->SetShowMouseCursor(true);

	AHumanPlayerPawn* Pawn = NewPlayer->GetPawn<AHumanPlayerPawn>();
	const int32 PlayerId = GetTypeHash(NewPlayer->GetPlayerState<APlayerState>()->GetUniqueId());

	UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();
	const FName RuledCountryTag = GameInstance->GetRuledCountry(PlayerId);
		
	Pawn->SetRuledCountryTag(RuledCountryTag);
}

void AGameLevelGameMode::CreateAIPawns()
{
	for (const auto& CountryTag : GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountriesTagsList())
	{
		if (GetGameInstance<UMyGameInstance>()->IsCountryRuledByPlayer(CountryTag)) continue;
		AAIPlayerPawn* Pawn = GetWorld()->SpawnActor<AAIPlayerPawn>(AAIPlayerPawn::StaticClass());
		Pawn->SetRuledCountryTag(CountryTag);
		AIPawns.Add(CountryTag, Pawn);
	}
}
