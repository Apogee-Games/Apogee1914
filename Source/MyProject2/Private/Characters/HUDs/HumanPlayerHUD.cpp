#include "Characters/HUDs/HumanPlayerHUD.h"

#include "MyGameInstance.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Administration/Managers/CountriesManager.h"
#include "People/Managers/PeopleManager.h"

void AHumanPlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	InitProvinceDataWidget();
	InitUnitTypesListWidget();
	InitBuildingsTypesListWidget();
	InitStorageGoodsListWidget();
	InitUnitsSupplyListWidget();
	InitUnitInstancesListDescriptionWidget();
	InitTimeControllerWidget();
	InitUnitsCollectionsListWidget();
	InitCommanderListWidget();
	InitMenuWidget();
	InitTopPanelWidget();
	InitCountryDiplomacyWidget();
	InitWarsListWidget();
	InitWarDescriptionWidget();
	InitMapsSwitcher();
	InitAllianceCreationWidget();
	InitWarsLists();
	InitCountryManagementWidget();
	InitLawsWidget();
	InitMusicControllerWidget();
	InitProductionListWidget();
	InitProducibleGoodsListWidget();
}

UProvinceDataWidget* AHumanPlayerHUD::GetProvinceDataWidget() const
{
	return ProvinceDataWidget;
}

UUnitTypesListWidget* AHumanPlayerHUD::GetUnitTypesListWidget() const
{
	return UnitTypesListWidget;
}

UStorageGoodsListWidget* AHumanPlayerHUD::GetStorageGoodsListWidget() const
{
	return StorageGoodsListWidget;
}

UUnitsSupplyListWidget* AHumanPlayerHUD::GetUnitsSupplyListWidget() const
{
	return UnitsSupplyListWidget;
}

USelectedUnitsListWidget* AHumanPlayerHUD::GetUnitInstancesListDescriptionWidget() const
{
	return UnitInstancesListDescriptionWidget;
}

UTimeControllerWidget* AHumanPlayerHUD::GetTimeControllerWidget()
{
	if (!TimeControllerWidget)
	{
		InitTimeControllerWidget();
	}
	return TimeControllerWidget;
}

UBuildingsTypesListWidget* AHumanPlayerHUD::GetBuildingsTypesListWidget() const
{
	return BuildingsTypesListWidget;
}

UUnitsCollectionsListWidget* AHumanPlayerHUD::GetUnitsCollectionsListWidget() const
{
	return UnitsCollectionsListWidget;
}

UCommanderListWidget* AHumanPlayerHUD::GetCommanderListWidget() const
{
	return CommanderListWidget;
}

UMenuWidget* AHumanPlayerHUD::GetMenuWidget() const
{
	return MenuWidget;
}

UTopPanelWidget* AHumanPlayerHUD::GetTopPanelWidget() const
{
	return TopPanelWidget;
}

UCountryDiplomacyWidget* AHumanPlayerHUD::GetCountryDiplomacyWidget() const
{
	return CountryDiplomacyWidget;
}

UWarsListWidget* AHumanPlayerHUD::GetWarsListWidget() const
{
	return WarsListWidget;
}

UWarDescriptionWidget* AHumanPlayerHUD::GetWarDescriptionWidget() const
{
	return WarDescriptionWidget;
}

UAllianceCreationWidget* AHumanPlayerHUD::GetAllianceCreationWidget() const
{
	return AllianceCreationWidget;
}

UOurWarsListWidget* AHumanPlayerHUD::GetOurWarsListWidget() const
{
	return OurWarsListWidget;
}

UTheirWarsListWidget* AHumanPlayerHUD::GetTheirWarsListWidget() const
{
	return TheirWarsListWidget;
}

void AHumanPlayerHUD::UpdateWidgetsVisibility()
{
	const TSharedPtr<FPawnState> PawnState = Cast<AHumanPlayerPawn>(GetOwningPawn())->GetPawnState();
	
	for (const auto& Widget: Widgets)
	{
		if (PawnState->MustWidgetBeVisible(Widget))
		{
			Widget->AddToPlayerScreen();
			continue;
		}
		
		if (PawnState->CanWidgetBeVisible(Widget))
		{
			continue;
		}
		
		Widget->RemoveFromViewport();
	}
}


void AHumanPlayerHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	for (const auto& Widget: Widgets)
	{
		Widget->RemoveFromParent();
	}
	if (TimeControllerWidget)
	{
		TimeControllerWidget->RemoveFromParent();
	}
	if (UnitsCollectionsListWidget)
	{
		UnitsCollectionsListWidget->RemoveFromParent();
	}
	if (MenuWidget)
	{
		MenuWidget->RemoveFromParent();
	}
	if (TopPanelWidget)
	{
		TopPanelWidget->RemoveFromParent();
	}
	if (WarsListWidget)
	{
		WarsListWidget->RemoveFromParent();
	}
	if (MapsSwitcherWidget)
	{
		MapsSwitcherWidget->RemoveFromParent();
	}
}

void AHumanPlayerHUD::InitProvinceDataWidget()
{
	if (ProvinceDataWidgetClass)
	{
		ProvinceDataWidget = CreateWidget<UProvinceDataWidget>(GetOwningPlayerController(), ProvinceDataWidgetClass);
		if (ProvinceDataWidget)
		{
			Widgets.Add(ProvinceDataWidget);
		}
	}
}

void AHumanPlayerHUD::InitUnitTypesListWidget()
{
	if (UnitTypesListWidgetClass)
	{
		UnitTypesListWidget = CreateWidget<UUnitTypesListWidget>(GetOwningPlayerController(), UnitTypesListWidgetClass);
		
		if (UnitTypesListWidget)
		{
			UnitTypesListWidget->Init();
			Widgets.Add(UnitTypesListWidget);
		}
	}
}

void AHumanPlayerHUD::InitStorageGoodsListWidget()
{
	if (StorageGoodsListWidgetClass)
	{
		StorageGoodsListWidget = CreateWidget<UStorageGoodsListWidget>(GetOwningPlayerController(), StorageGoodsListWidgetClass);
		if (StorageGoodsListWidget)
		{
			const FName RuledCountryTag = Cast<AHumanPlayerPawn>(GetOwningPawn())->GetRuledCountryTag();
			const UCountry* Country = GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry(RuledCountryTag);

			for (const auto& Storage: Country->GetStorages())
			{
				Storage->AddStorageObserver(StorageGoodsListWidget);
			}

			Widgets.Add(StorageGoodsListWidget);
		}
	}
}

void AHumanPlayerHUD::InitUnitsSupplyListWidget()
{
	if (UnitsSupplyListWidgetClass)
	{
		UnitsSupplyListWidget = CreateWidget<UUnitsSupplyListWidget>(GetOwningPlayerController(), UnitsSupplyListWidgetClass);
		if (UnitsSupplyListWidget)
		{
			UnitsSupplyListWidget->Init();
			Widgets.Add(UnitsSupplyListWidget);
		}
	}
}


void AHumanPlayerHUD::InitUnitInstancesListDescriptionWidget()
{
	if (UnitInstancesListDescriptionWidgetClass)
	{
		UnitInstancesListDescriptionWidget = CreateWidget<USelectedUnitsListWidget>(GetOwningPlayerController(), UnitInstancesListDescriptionWidgetClass);
		if (UnitInstancesListDescriptionWidget)
		{
			UnitInstancesListDescriptionWidget->Init();
			Widgets.Add(UnitInstancesListDescriptionWidget);
		}
	}
}

void AHumanPlayerHUD::InitBuildingsTypesListWidget()
{
	if (BuildingsTypesListWidgetClass)
	{
		BuildingsTypesListWidget = CreateWidget<UBuildingsTypesListWidget>(GetOwningPlayerController(), BuildingsTypesListWidgetClass);
		
		if (BuildingsTypesListWidget)
		{
			BuildingsTypesListWidget->Init(GetGameInstance<UMyGameInstance>()->ActiveScenario->BuildingsDescriptions);
			Widgets.Add(BuildingsTypesListWidget);
		}
	}
	
}

void AHumanPlayerHUD::InitTimeControllerWidget()
{
	if (!TimeControllerWidget && TimeControllerClass)
	{
		TimeControllerWidget = CreateWidget<UTimeControllerWidget>(GetOwningPlayerController(), TimeControllerClass);
		if (TimeControllerWidget)
		{
			TimeControllerWidget->AddToPlayerScreen(2);
		}
	}
}

void AHumanPlayerHUD::InitUnitsCollectionsListWidget()
{
	if (UnitsCollectionsListWidgetClass)
	{
		UnitsCollectionsListWidget = CreateWidget<UUnitsCollectionsListWidget>(GetOwningPlayerController(), UnitsCollectionsListWidgetClass);
		if (UnitsCollectionsListWidget) {
			UnitsCollectionsListWidget->AddToPlayerScreen();
		}
	}
}

void AHumanPlayerHUD::InitCommanderListWidget()
{
	if (CommanderListWidgetClass)
	{
		CommanderListWidget = CreateWidget<UCommanderListWidget>(GetOwningPlayerController(), CommanderListWidgetClass);
		if (CommanderListWidget)
		{
			CommanderListWidget->Init();
			Widgets.Add(CommanderListWidget);
		}	
	}
}

void AHumanPlayerHUD::InitMenuWidget()
{
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UMenuWidget>(GetOwningPlayerController(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->Init();
		}
	}
}

void AHumanPlayerHUD::InitTopPanelWidget()
{
	if (TopPanelWidgetClass)
	{
		TopPanelWidget = CreateWidget<UTopPanelWidget>(GetOwningPlayerController(), TopPanelWidgetClass);
		if (TopPanelWidget)
		{
			TopPanelWidget->AddToPlayerScreen(1);
		}
	}
}

void AHumanPlayerHUD::InitCountryDiplomacyWidget()
{
	if (CountryDiplomacyWidgetClass)
	{
		CountryDiplomacyWidget = CreateWidget<UCountryDiplomacyWidget>(GetOwningPlayerController(), CountryDiplomacyWidgetClass);
		if (CountryDiplomacyWidget)
		{
			CountryDiplomacyWidget->Init();
			Widgets.Add(CountryDiplomacyWidget);
		}
	}
}

void AHumanPlayerHUD::InitWarsListWidget()
{
	if (WarsListWidgetClass)
	{
		WarsListWidget = CreateWidget<UWarsListWidget>(GetOwningPlayerController(), WarsListWidgetClass);
		if (WarsListWidget)
		{
			WarsListWidget->AddToPlayerScreen();
		}
	}
}

void AHumanPlayerHUD::InitWarDescriptionWidget()
{
	if (WarDescriptionWidgetClass)
	{
		WarDescriptionWidget = CreateWidget<UWarDescriptionWidget>(GetOwningPlayerController(), WarDescriptionWidgetClass);
		if (WarDescriptionWidget)
		{
			Widgets.Add(WarDescriptionWidget);
		}
	}
}

void AHumanPlayerHUD::InitMapsSwitcher()
{
	if (MapsSwitcherWidgetClass)
	{
		MapsSwitcherWidget = CreateWidget<UMapsSwitcherWidget>(GetOwningPlayerController(), MapsSwitcherWidgetClass);
		if (MapsSwitcherWidget)
		{
			MapsSwitcherWidget->AddToPlayerScreen();
		}
	}
}

void AHumanPlayerHUD::InitAllianceCreationWidget()
{
	if (AllianceCreationWidgetClass)
	{
		AllianceCreationWidget = CreateWidget<UAllianceCreationWidget>(GetOwningPlayerController(), AllianceCreationWidgetClass);
		if (AllianceCreationWidget)
		{
			AllianceCreationWidget->Init();
			Widgets.Add(AllianceCreationWidget);
		}
	}
}

void AHumanPlayerHUD::InitWarsLists()
{
	if (OurWarsListWidgetClass)
	{
		OurWarsListWidget = CreateWidget<UOurWarsListWidget>(GetOwningPlayerController(), OurWarsListWidgetClass);
		if (OurWarsListWidget)
		{
			Widgets.Add(OurWarsListWidget);
		}
	}
	if (TheirWarsListWidgetClass)
	{
		TheirWarsListWidget = CreateWidget<UTheirWarsListWidget>(GetOwningPlayerController(), TheirWarsListWidgetClass);
		if (TheirWarsListWidget)
		{
			Widgets.Add(TheirWarsListWidget);
		}
	}
}

void AHumanPlayerHUD::InitCountryManagementWidget()
{
	if (CountryManagementWidgetClass)
	{
		CountryManagementWidget = CreateWidget<UCountryManagementWidget>(GetOwningPlayerController(), CountryManagementWidgetClass);
		if (CountryManagementWidget)
		{
			Widgets.Add(CountryManagementWidget);
		}
	}
}

void AHumanPlayerHUD::InitLawsWidget()
{
	if (LawsWidgetClass)
	{
		LawsWidget = CreateWidget<ULawsWidget>(GetOwningPlayerController(), LawsWidgetClass);
		if (LawsWidget)
		{
			LawsWidget->Init();
			Widgets.Add(LawsWidget);
		}
	}
}

void AHumanPlayerHUD::InitMusicControllerWidget()
{
	if (MusicControllerWidgetClass)
	{
		MusicControllerWidget = CreateWidget<UMusicControllerWidget>(GetOwningPlayerController(), MusicControllerWidgetClass);
		UDataTable* SongsDescriptionsDataTable = GetGameInstance<UMyGameInstance>()->ActiveScenario->SongsDescriptionsDataTable;
		for (const auto& [Name, SongDescription]: SongsDescriptionsDataTable->GetRowMap())
		{
			MusicControllerWidget->AddSong(reinterpret_cast<FSongDescription*>(SongDescription));
		}
		MusicControllerWidget->AddToPlayerScreen(1);
	}
}

void AHumanPlayerHUD::InitProductionListWidget()
{
	if (ProductionListWidgetClass)
	{
		ProductionListWidget = CreateWidget<UProductionListWidget>(GetOwningPlayerController(), ProductionListWidgetClass);
		if (ProductionListWidget)
		{
			ProductionListWidget->Init();
			Widgets.Add(ProductionListWidget);
		}
	}
}

void AHumanPlayerHUD::InitProducibleGoodsListWidget()
{
	if (ProducibleGoodsListWidgetClass)
	{
		ProducibleGoodsListWidget = CreateWidget<UProducibleGoodsListWidget>(GetOwningPlayerController(), ProducibleGoodsListWidgetClass);
		if (ProducibleGoodsListWidget)
		{
			Widgets.Add(ProducibleGoodsListWidget);
		}
	}
}
