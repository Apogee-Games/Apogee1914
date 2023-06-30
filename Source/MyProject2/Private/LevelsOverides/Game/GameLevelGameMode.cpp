// Copyright Epic Games, Inc. All Rights Reserved.


#include "LevelsOverides/Game/GameLevelGameMode.h"

#include "AIController.h"
#include "InGameTime.h"
#include "MyGameInstance.h"
#include "Administration/Managers/CountriesManager.h"
#include "Characters/AIPlayerController.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "GameFramework/PlayerState.h"
#include "Characters/AIPlayerPawn.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Events/EventInstancesController.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/MapsDataGatherer.h"

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
	GetGameInstance()->GetSubsystem<UEventInstancesController>()->Tick(DeltaSeconds);
	GetGameInstance()->GetSubsystem<UInGameTime>()->Tick(DeltaSeconds);
}

void AGameLevelGameMode::BeginPlay()
{
	// Add Unit Descriptions -> Add Widget For Unit Creation -> Tie Widget and Unit Creation

	//GetWorld()->Exec(GetWorld(), TEXT("viewmode unlit"));

	Super::BeginPlay();

	UMapsDataGatherer* MapsDataGatherer = GetGameInstance()->GetSubsystem<UMapsDataGatherer>();
	AMapActor* MapActor = GetWorld()->GetFirstPlayerController()->GetPawn<AHumanPlayerPawn>()->GetMapActor();
	for (const auto& Province : GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces())
	{
		const FVector2d MapPosition = MapsDataGatherer->GetProvinceCenter(Province->GetId());
		const FVector3d WorldPosition = MapActor->GetWorldPosition(MapPosition);

		const FVector2d TopLeft = MapsDataGatherer->GetLeftTopCorner(Province);
		const FVector2d BottomRight = MapsDataGatherer->GetRightBottomCorner(Province);

		Province->InitProvinceActor(WorldPosition, TopLeft, BottomRight);
	}
	
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
	
	CreateAIPawns();
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

	UCountry* Country = GetGameInstance<UMyGameInstance>()->GetRuledCountry(NewPlayer);
	NewPlayer->GetPawn<AHumanPlayerPawn>()->SetRuledCountry(Country);
}

void AGameLevelGameMode::CreateAIPawns()
{
	UCountriesManager* CountriesManager = GetGameInstance()->GetSubsystem<UCountriesManager>();
	for (const auto& CountryDescription : GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountriesDescriptions())
	{
		if (GetGameInstance<UMyGameInstance>()->IsCountryRuledByPlayer(CountryDescription)) continue; // TODO: Filter only active countries
		if (CountryDescription->Tag != "FRA") continue; // TODO: Remove this :)
		AAIPlayerController* Controller = GetWorld()->SpawnActor<AAIPlayerController>(AIPlayerControllerClass);
		AAIPlayerPawn* Pawn = GetWorld()->SpawnActor<AAIPlayerPawn>(AAIPlayerPawn::StaticClass());
		Controller->Possess(Pawn);
		Pawn->SetRuledCountry(CountriesManager->GetCountry(CountryDescription));
		AIPawns.Add(CountryDescription, Pawn);
	}
}
