#pragma once
#include "GameFramework/HUD.h"
#include "MyProject2/Widgets/Administration/ProvinceDataWidget.h"
#include "MyProject2/Widgets/Economics/StorageGoodsListWidget.h"
#include "MyProject2/Widgets/Military/Creation/UnitTypesListWidget.h"
#include "MyProject2/Widgets/Military/Selection/UnitInstancesListDescriptionWidget.h"
#include "MyProject2/Widgets/Military/Supply/UnitsSupplyListWidget.h"
#include "HumanPlayerHUD.generated.h"

UCLASS()
class AHumanPlayerHUD: public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	UProvinceDataWidget* GetProvinceDataWidget() const;

	UUnitTypesListWidget* GetUnitTypesListWidget() const;

	UStorageGoodsListWidget* GetStorageGoodsListWidget() const;

	UUnitsSupplyListWidget* GetUnitsSupplyListWidget() const;

	UUnitInstancesListDescriptionWidget* GetUnitInstancesListDescriptionWidget() const;
	
	void UpdateWidgetsVisibility();
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY()
	UProvinceDataWidget* ProvinceDataWidget;

	UPROPERTY()
	UUnitTypesListWidget* UnitTypesListWidget;

	UPROPERTY()
	UStorageGoodsListWidget* StorageGoodsListWidget;

	UPROPERTY()
	UUnitsSupplyListWidget* UnitsSupplyListWidget;

	UPROPERTY()
	UUnitInstancesListDescriptionWidget* UnitInstancesListDescriptionWidget; 
	
	UPROPERTY()
	TArray<UUserWidget*> Widgets;

	void InitProvinceDataWidget();

	void InitUnitTypesListWidget();
	
	void InitStorageGoodsListWidget();

	void InitUnitsSupplyListWidget();

	void InitUnitInstancesListDescriptionWidget();
};
