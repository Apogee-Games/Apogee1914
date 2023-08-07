#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Economics/Instances/Buildings/Building.h"
#include "Economics/Managers/BuildingManager.h"
#include "ProductionListWidget.generated.h"

UCLASS()
class UProductionListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* FactoriesListView;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	UCountry* OwnerCountry;
	
	UFUNCTION()
	void OnBuildingStatusChanged(UBuilding* Building, EBuildingStatus BuildingStatus);
};
