#pragma once
#include "Administration/Instances/Fraction.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "FractionWidget.generated.h"
UCLASS()
class UFractionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* FractionNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MembersNumberTextBlock;

	UFUNCTION(BlueprintCallable)
	void SetFraction(UObject* ProvidedFraction);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UFraction* Fraction;
};
