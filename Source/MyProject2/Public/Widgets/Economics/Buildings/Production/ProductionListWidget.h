#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Economics/Interfaces/Observers/BuildingCreationObserver.h"
#include "ProductionListWidget.generated.h"

UCLASS()
class UProductionListWidget: public UUserWidget, public IBuildingCreationObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* FactoriesListView;

	void Init();

	virtual void BuildingIsCreated(UBuilding* Building) override;
};
