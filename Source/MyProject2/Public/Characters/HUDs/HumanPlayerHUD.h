#pragma once
#include "GameFramework/HUD.h"
#include "Widgets/TimeControllerWidget.h"
#include "Widgets/TopPanelWidget.h"
#include "Widgets/Administration/ProvinceDataWidget.h"
#include "Widgets/Administration/Country/CountryManagementWidget.h"
#include "Widgets/Administration/Laws/LawsGroupWidget.h"
#include "Widgets/Administration/Laws/LawsWidget.h"
#include "Widgets/Diplomacy/Wars/Description/WarDescriptionWidget.h"
#include "Widgets/Diplomacy/Wars/List//WarsListWidget.h"
#include "Widgets/Economics/Buildings/Creation/BuildingsTypesListWidget.h"
#include "Widgets/Economics/Storage/StorageGoodsListWidget.h"
#include "Widgets/Maps/MapsSwitcherWidget.h"
#include "Widgets/Menu/MenuWidget.h"
#include "Widgets/Military/Collections/UnitsCollectionsListWidget.h"
#include "Widgets/Military/Commanders/CommanderListWidget.h"
#include "Widgets/Military/Creation/UnitTypesListWidget.h"
#include "Widgets/Military/Selection/SelectedUnitsListWidget.h"
#include "Widgets/Military/Supply/UnitsSupplyListWidget.h"
#include "Widgets/Diplomacy/Alliance/Creation/AllianceCreationWidget.h"
#include "Widgets/Diplomacy/Menu/CountryDiplomacyWidget.h"
#include "Widgets/Diplomacy/Wars/Join/OurWar/OurWarsListWidget.h"
#include "Widgets/Diplomacy/Wars/Join/TheirWar/TheirWarsListWidget.h"
#include "Widgets/Economics/Buildings/Production/ProducibleGoodsListWidget.h"
#include "Widgets/Economics/Buildings/Production/ProductionListWidget.h"
#include "Widgets/Music/MusicControllerWidget.h"
#include "HumanPlayerHUD.generated.h"

UCLASS()
class AHumanPlayerHUD: public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USelectedUnitsListWidget> UnitInstancesListDescriptionWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUnitsSupplyListWidget> UnitsSupplyListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UStorageGoodsListWidget> StorageGoodsListWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UProvinceDataWidget> ProvinceDataWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUnitTypesListWidget> UnitTypesListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBuildingsTypesListWidget> BuildingsTypesListWidgetClass; 
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTimeControllerWidget> TimeControllerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUnitsCollectionsListWidget> UnitsCollectionsListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCommanderListWidget> CommanderListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMenuWidget> MenuWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTopPanelWidget> TopPanelWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCountryDiplomacyWidget> CountryDiplomacyWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWarsListWidget> WarsListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWarDescriptionWidget> WarDescriptionWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMapsSwitcherWidget> MapsSwitcherWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAllianceCreationWidget> AllianceCreationWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOurWarsListWidget> OurWarsListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTheirWarsListWidget> TheirWarsListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCountryManagementWidget> CountryManagementWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULawsWidget> LawsWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMusicControllerWidget> MusicControllerWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UProductionListWidget> ProductionListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UProducibleGoodsListWidget> ProducibleGoodsListWidgetClass;
	
	virtual void BeginPlay() override;
	
	UTimeControllerWidget* GetTimeControllerWidget();
	UTopPanelWidget* GetTopPanelWidget() const;

	UMenuWidget* GetMenuWidget() const;

	UWarsListWidget* GetWarsListWidget() const;
	UUnitsCollectionsListWidget* GetUnitsCollectionsListWidget() const;

	void UpdateWidgetsVisibility();
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY()
	UTimeControllerWidget* TimeControllerWidget;

	UPROPERTY()
	UUnitsCollectionsListWidget* UnitsCollectionsListWidget;

	UPROPERTY()
	UMenuWidget* MenuWidget;

	UPROPERTY()
	UTopPanelWidget* TopPanelWidget;

	UPROPERTY()
	UWarsListWidget* WarsListWidget;

	UPROPERTY()
	UMapsSwitcherWidget* MapsSwitcherWidget;

	UPROPERTY()
	UMusicControllerWidget* MusicControllerWidget;

	UPROPERTY()
	TArray<UUserWidget*> Widgets;

	void InitTimeControllerWidget();
	void InitUnitsCollectionsListWidget();
	void InitMenuWidget();
	void InitTopPanelWidget();
	void InitWarsListWidget();
	void InitMapsSwitcher();
	void InitMusicControllerWidget();
};
