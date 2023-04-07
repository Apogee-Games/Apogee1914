#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Military/Instances/Units/Unit.h"
#include "Military/Interfaces/Observers/UnitCreationObserver.h"
#include "Military/Interfaces/Observers/UnitRemovalObserver.h"

#include "UnitsSupplyListWidget.generated.h"

UCLASS()
class UUnitsSupplyListWidget: public UUserWidget, public IUnitCreationObserver, public IUnitRemovalObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* UnitsListView;

	void Init();
	
	virtual void UnitIsCreated(UUnit* Unit) override;

	virtual void UnitIsRemoved(UUnit* Unit) override;
private:
	UPROPERTY()
	UCountry* Country;
};
