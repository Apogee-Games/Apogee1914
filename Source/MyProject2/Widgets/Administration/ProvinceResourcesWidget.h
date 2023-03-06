#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyProject2/Administration/Instances/ProvinceResource.h"
#include "ProvinceResourcesWidget.generated.h"

UCLASS()
class UProvinceResourcesWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ResourceNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UsedAmountTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* TotalAmountTextBlock;

	UFUNCTION(BlueprintCallable)
	void SetResource(UObject* ProvidedResource);

	UFUNCTION(BlueprintCallable)
	void RefreshData();

private:
	UPROPERTY()
	UProvinceResource* Resource;
};
