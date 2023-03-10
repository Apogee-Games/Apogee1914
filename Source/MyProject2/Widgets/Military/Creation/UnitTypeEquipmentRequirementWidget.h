#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyProject2/Widgets/Military/Carriers/GoodRequirementCarrier.h"
#include "UnitTypeEquipmentRequirementWidget.generated.h"

UCLASS()
class UUnitTypeEquipmentRequirementWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GoodNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* AmountTextBlock;

	UFUNCTION(BlueprintCallable)
	void SetCarrier(UObject* ProvidedCarrier);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UGoodRequirementCarrier* Carrier;
};
