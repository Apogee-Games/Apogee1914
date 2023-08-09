#include "Characters/HUDs/HumanPlayerHUD.h"

#include "MyGameInstance.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Administration/Managers/CountriesManager.h"
#include "People/Managers/PeopleManager.h"

void AHumanPlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	TArray<TSubclassOf<UUserWidget>> WidgetClasses = {
		ProvinceDataWidgetClass,
		UnitTypesListWidgetClass,
		BuildingsTypesListWidgetClass,
		StorageGoodsListWidgetClass,
		UnitsSupplyListWidgetClass,
		UnitInstancesListDescriptionWidgetClass,
		CommanderListWidgetClass,
		CountryDiplomacyWidgetClass,
		WarDescriptionWidgetClass,
		AllianceCreationWidgetClass,
		OurWarsListWidgetClass,
		TheirWarsListWidgetClass,
		CountryManagementWidgetClass,
		LawsWidgetClass,
		ProductionListWidgetClass,
		ProducibleGoodsListWidgetClass
	};

	for (TSubclassOf<UUserWidget> WidgetClass: WidgetClasses)
	{
		if (WidgetClass)
		{
			if (UUserWidget* Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(),  WidgetClass))
			{
				Widgets.Add(Widget);
			}
		}
	}
	
	InitTimeControllerWidget();
	InitUnitsCollectionsListWidget();
	InitMenuWidget();
	InitTopPanelWidget();
	InitWarsListWidget();
	InitMapsSwitcher();
	InitMusicControllerWidget();
}

UTimeControllerWidget* AHumanPlayerHUD::GetTimeControllerWidget()
{
	if (!TimeControllerWidget)
	{
		InitTimeControllerWidget();
	}
	return TimeControllerWidget;
}

UUnitsCollectionsListWidget* AHumanPlayerHUD::GetUnitsCollectionsListWidget() const
{
	return UnitsCollectionsListWidget;
}

UMenuWidget* AHumanPlayerHUD::GetMenuWidget() const
{
	return MenuWidget;
}

UTopPanelWidget* AHumanPlayerHUD::GetTopPanelWidget() const
{
	return TopPanelWidget;
}

UWarsListWidget* AHumanPlayerHUD::GetWarsListWidget() const
{
	return WarsListWidget;
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
		
		Widget->RemoveFromParent();
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

void AHumanPlayerHUD::InitMenuWidget()
{
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UMenuWidget>(GetOwningPlayerController(), MenuWidgetClass);
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

void AHumanPlayerHUD::InitMusicControllerWidget()
{
	if (MusicControllerWidgetClass)
	{
		MusicControllerWidget = CreateWidget<UMusicControllerWidget>(GetOwningPlayerController(), MusicControllerWidgetClass);
		if (MusicControllerWidget)
		{
			MusicControllerWidget->AddToPlayerScreen(1);
		}
	}
}

