#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/Economics/Buildings/Carriers/GoodProductionCarrier.h"
#include "GoodProductionWidget.generated.h"

UCLASS()
class UGoodProductionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GoodNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ProductionAmountTextBlock;
	
	UFUNCTION(BlueprintCallable)
	void SetCarrier(UObject* ProvidedCarrier);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
	
private:
	UGoodProductionCarrier* Carrier;
};
