#include "HumanPlayerHUD.h"

#include "HumanPlayerPawn.h"
#include "MyProject2/MyGameState.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"

void AHumanPlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	InitProvinceDataWidget();
	InitUnitTypesListWidget();
	InitStorageGoodsListWidget();
	InitUnitsSupplyListWidget();
	InitUnitInstancesListDescriptionWidget();
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
}

void AHumanPlayerHUD::InitProvinceDataWidget()
{
	const auto ProvinceDataWidgetClass = GetWorld()->GetGameState<AMyGameState>()->ProvinceDataWidgetClass;

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
	const auto UnitTypesListWidgetClass = GetWorld()->GetGameState<AMyGameState>()->UnitTypesListWidgetClass;
	
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
	const auto StorageGoodsListWidgetClass = GetWorld()->GetGameState<AMyGameState>()->StorageGoodsListWidgetClass;
	
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
	const TSubclassOf<UUnitsSupplyListWidget> UnitsSupplyListWidgetClass = GetWorld()->GetGameState<AMyGameState>()->UnitsSupplyListWidgetClass;
	
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
	const auto UnitInstancesListDescriptionWidgetClass = GetWorld()->GetGameState<AMyGameState>()->UnitInstancesListDescriptionWidgetClass;
	
	if (UnitInstancesListDescriptionWidgetClass)
	{
		UnitInstancesListDescriptionWidget = CreateWidget<UUnitInstancesListDescriptionWidget>(GetOwningPlayerController(), UnitInstancesListDescriptionWidgetClass);
		if (UnitInstancesListDescriptionWidget)
		{
			Widgets.Add(UnitInstancesListDescriptionWidget);
		}
	}
}