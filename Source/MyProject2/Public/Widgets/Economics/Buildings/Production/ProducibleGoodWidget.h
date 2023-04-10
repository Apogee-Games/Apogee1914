#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Economics/Description/Goods/CookedGoodDescription.h"
#include "ProducibleGoodWidget.generated.h"

UCLASS()
class UProducibleGoodWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* GoodImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GoodNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	UFUNCTION(BlueprintCallable)
	void SetGood(UObject* ProvidedGood);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
	
	virtual void NativeConstruct() override;
private:
	UPROPERTY()
	UCookedGoodDescription* Good;
	
	UFUNCTION()
	void OnButtonClick();
};

