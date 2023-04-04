#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Military/Instances/Units/Unit.h"

#include "UnitSupplyWidget.generated.h"

UCLASS()
class UUnitSupplyWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UnitNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UListView* SuppliesListView;
	
	UFUNCTION(BlueprintCallable)
	void SetUnit(UObject* ProvidedUnit);
	
	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UUnit* Unit;

	UPROPERTY()
	TSet<UGoodDescription*> AddedGoodNeeds;
};
