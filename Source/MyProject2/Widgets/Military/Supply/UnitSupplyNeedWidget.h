#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyProject2/Military/Instances/GoodNeedCarrier.h"
#include "UnitSupplyNeedWidget.generated.h"

UCLASS()
class UUnitSupplyNeedWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GoodNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GoodSupplyTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GoodRequirementTextBlock;

	UFUNCTION(BlueprintCallable)
	void SetCarrier(UObject* ProvidedCarrier);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UGoodNeedCarrier* Carrier;
	
};
