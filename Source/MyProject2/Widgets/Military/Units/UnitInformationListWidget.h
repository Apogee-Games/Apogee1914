#pragma once

#include "UnitInformationWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "UnitInformationListWidget.generated.h"


UCLASS()
class MYPROJECT2_API UUnitInformationListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UGridPanel* UnitsGridPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUnitInformationWidget> UnitInformationWidgetClass;
	
	void AddUnit(FUnit* Unit);

	void RemoveUnit(FUnit* Unit);
	
private:
	UPROPERTY()
	TMap<UCountry*, UUnitInformationWidget*> Widgets;

	void CheckWidgetsMapState(FUnit* Unit);
};
