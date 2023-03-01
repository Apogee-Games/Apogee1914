#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyProject2/Military/Instances/Units/Unit.h"
#include "UnitInstanceDescriptionWidget.generated.h"

UCLASS()
class UUnitInstanceDescriptionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* FlagImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ProvinceNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* UnitNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void Init(UObject* Object);

	void RefreshData();

private:
	UUnit* Unit;

	UFUNCTION()
	void OnClick();
};
