#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Military/Instances/Units/Unit.h"
#include "Military/Managers/UnitsFactory.h"
#include "UnitsSupplyListWidget.generated.h"

UCLASS()
class UUnitsSupplyListWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsListView;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	UCountry* OwnerCountry;

	UFUNCTION()
	void OnUnitStatusChanged(UUnit* Unit, EUnitStatus UnitStatus);
};
