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
	InitUnitsCollectionsWidget();
	InitCommanderListWidget();
	InitMenuWidget();
	InitTopPanelWidget();
	InitCountryDiplomacyWidget();
	InitWarsListWidget();
	InitWarDescriptionWidget();
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

UUnitsCollectionsWidget* AHumanPlayerHUD::GetUnitsCollectionsWidget() const
{
	return UnitsCollectionsWidget;
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
	if (UnitsCollectionsWidget)
	{
		UnitsCollectionsWidget->RemoveFromParent();
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
			UDataTable* UnitsDescriptionDataTable = GetGameInstance<UMyGameInstance>()->ActiveScenario->UnitsDescriptionDataTable;

			for (const auto& [UnitName, UnitDescription]: UnitsDescriptionDataTable->GetRowMap())
			{
				UnitTypesListWidget->AddUnitType(reinterpret_cast<FUnitDescription*>(UnitDescription));
			}
			
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

			UDataTable* BuildingsDescriptionDataTable = GetGameInstance<UMyGameInstance>()->ActiveScenario->BuildingsDescriptionDataTable;

			for (const auto& [BuildingName, BuildingDescription]: BuildingsDescriptionDataTable->GetRowMap())
			{
				BuildingsTypesListWidget->AddBuildingType(reinterpret_cast<FBuildingDescription*>(BuildingDescription));
			}
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
			TimeControllerWidget->AddToPlayerScreen();
		}
	}
}

void AHumanPlayerHUD::InitUnitsCollectionsWidget()
{
	if (UnitsCollectionsWidgetClass)
	{
		UnitsCollectionsWidget = CreateWidget<UUnitsCollectionsWidget>(GetOwningPlayerController(), UnitsCollectionsWidgetClass);
		if (UnitsCollectionsWidget) {
			UnitsCollectionsWidget->AddToPlayerScreen();
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
			FName CountryTag = Cast<AHumanPlayerPawn>(GetOwningPawn())->GetRuledCountryTag();
			const TArray<UPerson*> People = GetGameInstance()->GetSubsystem<UPeopleManager>()->GetPeopleByProfession(TEXT("Commander"), CountryTag);
			for (const auto& Person: People)
			{
				CommanderListWidget->AddCommander(Person);		
			}
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
			TopPanelWidget->AddToPlayerScreen();
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
