#pragma once
#include "UnitSupplyWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "MyProject2/Military/Instances/Units/Unit.h"
#include "MyProject2/Military/Interfaces/Observers/UnitCreationObserver.h"
#include "MyProject2/Military/Interfaces/Observers/UnitSupplyObserver.h"

#include "UnitsSupplyListWidget.generated.h"

UCLASS()
class UUnitsSupplyListWidget: public UUserWidget, public IUnitCreationObserver, public IUnitSupplyObserver
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UGridPanel* ListGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUnitSupplyWidget> UnitSupplyWidgetClass;

	void Init();
	
	virtual void UnitIsCreated(UUnit* Unit) override;
	
	virtual void UnitIsSupplied(UUnit* Unit) override;

private:
	TMap<UUnit*, UUnitSupplyWidget*> Widgets;

	int Count = 0;
};
