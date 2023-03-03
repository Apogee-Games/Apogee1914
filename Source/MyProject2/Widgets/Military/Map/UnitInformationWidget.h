#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyProject2/Military/Instances/Units/Unit.h"
#include "MyProject2/Widgets/Military/Carriers/UnitsListCarrier.h"
#include "UnitInformationWidget.generated.h"

UCLASS()
class UUnitInformationWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* FlagImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CountTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetCarrier(UObject* ProvidedCarrier);	

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UUnitsListCarrier* Carrier;
	
	UFUNCTION()
	void OnClicked();
};