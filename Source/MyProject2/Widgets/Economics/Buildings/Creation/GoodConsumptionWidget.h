#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyProject2/Widgets/Economics/Carriers/GoodConsumptionCarrier.h"
#include "GoodConsumptionWidget.generated.h"

UCLASS()
class UGoodConsumptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GoodNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UsedAmountTextBlock;
	
	UFUNCTION(BlueprintCallable)
	void SetCarrier(UObject* ProvidedCarrier);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UGoodConsumptionCarrier* Carrier;
	
};
