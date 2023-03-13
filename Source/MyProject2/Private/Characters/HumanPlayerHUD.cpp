#include "Characters/HumanPlayerHUD.h"

#include "Characters/HumanPlayerPawn.h"
#include "MyGameState.h"
#include "Administration/Managers/CountriesManager.h"

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

UUnitInstancesListDescriptionWidget* AHumanPlayerHUD::GetUnitInstancesListDescriptionWidget() const
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
	if (TimeControllerWidget) {
		TimeControllerWidget->RemoveFromParent();
	}
	if (UnitsCollectionsWidget)
	{
		UnitsCollectionsWidget->RemoveFromParent();
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
			UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/units_description"));

			for (const auto& [UnitName, UnitDescription]: DataTable->GetRowMap())
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
			const UCountry* Country = GetWorld()->GetSubsystem<UCountriesManager>()->GetCountry(RuledCountryTag);

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
		UnitInstancesListDescriptionWidget = CreateWidget<UUnitInstancesListDescriptionWidget>(GetOwningPlayerController(), UnitInstancesListDescriptionWidgetClass);
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
			UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/buildings_description"));

			for (const auto& [BuildingName, BuildingDescription]: DataTable->GetRowMap())
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
		UnitsCollectionsWidget->AddToPlayerScreen();
	}
}
