#pragma once

#include "UnitInformationWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "UnitInformationListWidget.generated.h"


UCLASS()
class MYPROJECT2_API UUnitInformationListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsListView;
	
	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);
private:
	UPROPERTY()
	TMap<UCountry*, UUnitsListCarrier*> Widgets;

	void CheckWidgetsMapState(UUnit* Unit);
};
