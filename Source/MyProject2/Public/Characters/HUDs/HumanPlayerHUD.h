#pragma once
#include "GameFramework/HUD.h"
#include "Widgets/TimeControllerWidget.h"
#include "Widgets/Administration/ProvinceDataWidget.h"
#include "Widgets/Economics/Buildings/Creation/BuildingsTypesListWidget.h"
#include "Widgets/Economics/Storage/StorageGoodsListWidget.h"
#include "Widgets/Menu/MenuWidget.h"
#include "Widgets/Military/Collections/UnitsCollectionsWidget.h"
#include "Widgets/Military/Commanders/CommanderListWidget.h"
#include "Widgets/Military/Creation/UnitTypesListWidget.h"
#include "Widgets/Military/Selection/SelectedUnitsListWidget.h"
#include "Widgets/Military/Supply/UnitsSupplyListWidget.h"
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
	TSubclassOf<UUnitsCollectionsWidget> UnitsCollectionsWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCommanderListWidget> CommanderListWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMenuWidget> MenuWidgetClass;
	
	virtual void BeginPlay() override;
	
	UProvinceDataWidget* GetProvinceDataWidget() const;

	UUnitTypesListWidget* GetUnitTypesListWidget() const;

	UStorageGoodsListWidget* GetStorageGoodsListWidget() const;

	UUnitsSupplyListWidget* GetUnitsSupplyListWidget() const;

	USelectedUnitsListWidget* GetUnitInstancesListDescriptionWidget() const;

	UTimeControllerWidget* GetTimeControllerWidget();

	UBuildingsTypesListWidget* GetBuildingsTypesListWidget() const;
	
	UUnitsCollectionsWidget* GetUnitsCollectionsWidget() const;

	UCommanderListWidget* GetCommanderListWidget() const;

	UMenuWidget* GetMenuWidget() const;
	
	void UpdateWidgetsVisibility();
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY()
	UProvinceDataWidget* ProvinceDataWidget;

	UPROPERTY()
	UUnitTypesListWidget* UnitTypesListWidget;
	
	UPROPERTY()
	UBuildingsTypesListWidget* BuildingsTypesListWidget;
	
	UPROPERTY()
	UStorageGoodsListWidget* StorageGoodsListWidget;

	UPROPERTY()
	UUnitsSupplyListWidget* UnitsSupplyListWidget;

	UPROPERTY()
	USelectedUnitsListWidget* UnitInstancesListDescriptionWidget; 

	UPROPERTY()
	UTimeControllerWidget* TimeControllerWidget;

	UPROPERTY()
	UUnitsCollectionsWidget* UnitsCollectionsWidget;

	UPROPERTY()
	UCommanderListWidget* CommanderListWidget;

	UPROPERTY()
	UMenuWidget* MenuWidget;
	
	UPROPERTY()
	TArray<UUserWidget*> Widgets;

	void InitProvinceDataWidget();

	void InitUnitTypesListWidget();
	
	void InitStorageGoodsListWidget();

	void InitUnitsSupplyListWidget();

	void InitUnitInstancesListDescriptionWidget();

	void InitBuildingsTypesListWidget();
	
	void InitTimeControllerWidget();

	void InitUnitsCollectionsWidget();

	void InitCommanderListWidget();

	void InitMenuWidget();
};
