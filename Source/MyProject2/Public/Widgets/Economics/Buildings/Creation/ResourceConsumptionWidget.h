#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/Economics/Buildings/Carriers/ResourceConsumptionCarrier.h"
#include "ResourceConsumptionWidget.generated.h"

UCLASS()
class UResourceConsumptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ResourceNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UsedAmountTextBlock;

	UFUNCTION(BlueprintCallable)
	void SetCarrier(UObject* ProvidedCarrier);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UResourceConsumptionCarrier* Carrier;
	
};
