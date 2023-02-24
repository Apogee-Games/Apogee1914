#pragma once

#include "UnitInformationWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "MyProject2/Military/Instances/Unit.h"
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
	
	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);
	
private:
	UPROPERTY()
	TMap<UCountry*, UUnitInformationWidget*> Widgets;

	void CheckWidgetsMapState(UUnit* Unit);
};
