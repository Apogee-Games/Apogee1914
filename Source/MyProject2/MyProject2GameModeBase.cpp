// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProject2GameModeBase.h"

#include "MyGameInstance.h"
#include "MyGameState.h"
#include "Administration/Managers/CountriesManager.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Characters/HumanPlayerPawn.h"
#include "Characters/MyPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Characters/AIPlayerPawn.h"
#include "Economics/Managers/Public/BuildingManager.h"
#include "Events/EventInstancesController.h"
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

	//GetWorld()->Exec(GetWorld(), TEXT("viewmode unlit"));
	
	// Beginning of Units Renderer/Factory Test Logic
	
	FUnitDescription* UnitDescription = new FUnitDescription();
	UnitDescription->CanTransport = true;
	UnitDescription->UnitName = "Unit2";
	UnitDescription->CanAccessProvincesTypes.Add("Land");

	UUnitsRenderer* Renderer = GetWorld()->GetSubsystem<UUnitsRenderer>();
	
	UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	
	UUnit* Unit1 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(UnitDescription, ProvinceManager->GetProvince(FColor(202, 160, 1)), "GER",Renderer);
	UUnit* Unit2 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(UnitDescription,  ProvinceManager->GetProvince(FColor(246, 39, 1)), "GER",Renderer);
	UUnit* Unit3 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(UnitDescription,  ProvinceManager->GetProvince(FColor(239, 236, 1)), "GER",Renderer);
	UUnit* Unit4 = GetWorld()->GetSubsystem<UUnitsFactory>()->Create(UnitDescription,  ProvinceManager->GetProvince(FColor(231, 116, 1)), "NET",Renderer);

	GetWorld()->GetSubsystem<UUnitsMover>()->SetGraph(new FGraph({}));
	
	// End of Test Logic

	UnitTypesListWidget = CreateWidget<UUnitTypesListWidget>(GetWorld(), GetGameState<AMyGameState>()->UnitTypesListWidgetClass);

	if (UnitTypesListWidget)
	{
		UnitTypesListWidget->AddToPlayerScreen();
		UnitTypesListWidget->AddUnitType(UnitDescription);
		UnitTypesListWidget->AddUnitType(UnitDescription);
		UnitTypesListWidget->AddUnitType(UnitDescription);
	}
	
	// Beginning of Building Manager Test

	FBuildingDescription* BuildingDescription = new FBuildingDescription;

	BuildingDescription->GoodOutput = {{"Coal", 10}, {"Iron", 20}};
	
	BuildingDescription->MaxLabours = 10;

	UProvince* Province = ProvinceManager->GetProvince(FColor(202, 160, 1));
	
	GetWorld()->GetSubsystem<UBuildingManager>()->BuildBuilding(BuildingDescription, Province, Province->GetCountryController()->GetStorage());

	UBuilding* Building = GetWorld()->GetSubsystem<UBuildingManager>()->BuildBuilding(BuildingDescription, Province, Province->GetCountryController()->GetStorage());
	GetWorld()->GetSubsystem<UBuildingManager>()->DestroyBuilding(Building);

	GetWorld()->GetSubsystem<UBuildingManager>()->Produce();

	// End of Test Logic

	Super::BeginPlay();
	
	// Temporary initialization of Ruled tag will be removed when lobby will be added
	const int32 LocalPlayerControllersNumber = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int32 PlayerIndex = 0; PlayerIndex < LocalPlayerControllersNumber; ++PlayerIndex)
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
	if (UnitTypesListWidget)
	{
		UnitTypesListWidget->RemoveFromRoot();
		UnitTypesListWidget->RemoveFromViewport();
	}
}

void AMyProject2GameModeBase::InitializeRuledCountry() const
{
	InitializeRuledCountryForLocalPlayers();
	// TODO:: Add Ruled Country initialization for net Players
}

void AMyProject2GameModeBase::InitializeRuledCountryForLocalPlayers() const
{
	const int32 LocalPlayerControllersNumber = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int32 PlayerIndex = 0; PlayerIndex < LocalPlayerControllersNumber; ++PlayerIndex)
	{
		const AMyPlayerController* Controller = static_cast<AMyPlayerController*>(UGameplayStatics::GetPlayerController(
			GetWorld(), PlayerIndex));

		AHumanPlayerPawn* Pawn = Controller->GetPawn<AHumanPlayerPawn>();
		const int32 PlayerId = Pawn->GetPlayerState()->GetPlayerId();

		const UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();
		const FName RuledCountryTag = GameInstance->GetRuledCountry(PlayerId);
		
		Pawn->SetRuledCountryTag(RuledCountryTag);
	}
}

void AMyProject2GameModeBase::CreateAIPawns()
{
	for (const auto& CountryTag : GetWorld()->GetSubsystem<UCountriesManager>()->GetCountriesTagsList())
	{
		if (GetGameInstance<UMyGameInstance>()->IsCountryRuledByPlayer(CountryTag)) continue;
		AAIPlayerPawn* Pawn = GetWorld()->SpawnActor<AAIPlayerPawn>(AAIPlayerPawn::StaticClass());
		Pawn->SetRuledCountryTag(CountryTag);
		AIPawns.Add(CountryTag, Pawn);
	}
}
