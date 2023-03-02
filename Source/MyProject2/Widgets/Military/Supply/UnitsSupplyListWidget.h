#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "MyProject2/Military/Instances/Units/Unit.h"
#include "MyProject2/Military/Interfaces/Observers/UnitCreationObserver.h"

#include "UnitsSupplyListWidget.generated.h"

UCLASS()
class UUnitsSupplyListWidget: public UUserWidget, public IUnitCreationObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsListView;

	void Init();

	virtual void UnitIsCreated(UUnit* Unit) override;
};
