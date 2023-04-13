#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Military/Instances/Units/Unit.h"
#include "SelectedUnitWidget.generated.h"

UCLASS()
class USelectedUnitWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ProvinceNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UnitNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ManpowerTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* RemoveUnitButton;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void Init(UObject* Object);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UUnit* Unit;

	UFUNCTION()
	void OnButtonClick();

	UFUNCTION()
	void OnRemoveUnitButtonClick();
};
